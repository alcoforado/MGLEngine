#include "VulkanMemoryManager.h"
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../VulkanContext/VulkanPhysicalDevice.h"
#include <algorithm>
#include "../VulkanUtils.h"
#include <MGLEngine.Shared/Utils/Exception.h>

const int _MB = 1048576;



VulkanMemoryChunk::VulkanMemoryChunk(VulkanMemoryManager *parent, uint32_t memoryTypeIndex,uint64_t size)
{
	_parent = parent;
	
	//allocate memory
	_allocInfo = {};
	_allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	_allocInfo.allocationSize = size;
	_allocInfo.memoryTypeIndex = memoryTypeIndex;

	VkResult err = vkAllocateMemory(parent->GetLogicalDevice()->GetHandle(), &_allocInfo, nullptr, &_memoryHandle);
	AssertVulkanSuccess(err);

	_totalFree = size;
	_size = size;
	_maxBlockSize = size;

	_pBiggestBlock = new VulkanMemoryBlock(this, 0,size);
	_blocks.push_back(_pBiggestBlock);
	_isMapped = false;
}

void VulkanMemoryChunk::ComputeFreeBlocksSize()
{
	this->_maxBlockSize = 0;
	this->_totalFree = 0;
	VulkanMemoryBlock *prevFreeBlock = nullptr;
	for (auto it=_blocks.begin();it!=_blocks.end();++it)
	{
		VulkanMemoryBlock *block = *it;
		if (block->IsFree)
		{
			_totalFree += block->Size;
			if (prevFreeBlock)
			{
				prevFreeBlock->AlignedOff = 0;
				prevFreeBlock->TotalSize += block->TotalSize;
				prevFreeBlock->Size = prevFreeBlock->TotalSize;
				prevFreeBlock->AlignmentOffset = 0;
				it=_blocks.erase(it);
				--it;
				block = prevFreeBlock;
			}
			if (block->IsFree && block->Size >= _maxBlockSize)
			{
				_pBiggestBlock = block;
				_maxBlockSize = block->Size;
			}
			prevFreeBlock = block;
		}
		else
			prevFreeBlock = nullptr;
	}
}

VulkanMemoryBlock* VulkanMemoryChunk::TryToAllocate(uint32_t memoryIndex, uint64_t alignment,uint64_t size)
{
	for (auto it=_blocks.begin();it!=_blocks.end();it++)
	{
		VulkanMemoryBlock *block = *it;
		uint64_t rest = (alignment - block->Off%alignment) % alignment;
		if (block->IsFree && block->Size>= size+rest)
		{
			
			if (block->Size > size + rest)
			{
				auto newBlock = new VulkanMemoryBlock(this,block->AlignedOff + size,  block->Size - size - rest);
				it=this->_blocks.insert((++it),newBlock);
			}
			block->AlignedOff = block->Off + rest;
			block->IsFree = false;
			block->Size = size;
			block->TotalSize = size + rest;
			block->AlignmentOffset = rest;
			this->_totalFree -= block->TotalSize;
			if (block == _pBiggestBlock)
			{
				this->ComputeFreeBlocksSize();
			}
			return block;
		}

	}
	return nullptr;
}

void VulkanMemoryChunk::Map()
{
	if (!_isMapped)
	{
		void *p = nullptr;
		VkResult err = vkMapMemory(_parent->GetLogicalDevice()->GetHandle(), _memoryHandle,0, _size, 0, &p);
		_data = static_cast<char*>(p);
		_isMapped = true;

		AssertVulkanSuccess(err);
	}
}

void VulkanMemoryChunk::Flush(size_t offset, size_t sizeInBytes)
{
	VkMappedMemoryRange memRange = {};
	memRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	memRange.memory = _memoryHandle;
	memRange.offset = offset;
	memRange.size = sizeInBytes;

	VkResult result = vkFlushMappedMemoryRanges(_parent->GetLogicalDevice()->GetHandle(), 1, &memRange);
	AssertVulkanSuccess(result);
	return;
}

VulkanMemoryManager::VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeInBytes)
:_device(device)
{
	_blockSize = blockSizeInBytes;
}


VulkanMemoryManager::~VulkanMemoryManager()
{
}

void MemoryHandle::BindBuffer(VkBuffer buff) const
{
	_block->BindBuffer(buff);
}

void MemoryHandle::Free()
{
	_block->Free();
}

uint64_t MemoryHandle::GetOffset() const
{
	return _block->GetOffset();
}

void MemoryHandle::Flush()
{
	_block->GetChunk()->Flush(_block->GetOffset(),_block->GetSizeInByte());
}


MemoryHandle VulkanMemoryManager::Allocate(uint32_t memoryTypeIndex, uint64_t alignment, uint64_t size)
{
	VulkanMemoryBlock* result;
	assert(memoryTypeIndex < _device.GetPhysicalDevice().GetMemoryProperties().size());
	for (VulkanMemoryChunk *chunk : _chunks)
	{
		if (size <= chunk->_maxBlockSize && chunk->_allocInfo.memoryTypeIndex == memoryTypeIndex)
		{
			result = chunk->TryToAllocate(memoryTypeIndex, alignment, size);
			if (result)
			{
				return result;;
			}
		}
	}

	//
	_chunks.push_back(new VulkanMemoryChunk(this, memoryTypeIndex, std::max(_blockSize, size)));
	result = _chunks.back()->TryToAllocate(memoryTypeIndex, alignment, size);
	if (result)
	{
		return result;
	}
	else
		throw new Exception("alghorithm problem, new allocated chunk should always be allocable to the request");


}




MemoryHandle VulkanMemoryManager::Allocate(VkBuffer buffer, const std::vector<enum VkMemoryPropertyFlagBits>& vFlags)
{
	VkFlags flags = BitwiseOr(vFlags);
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(this->GetLogicalDevice()->GetHandle(), buffer, &memRequirements);

	auto memoryProperties = this->GetLogicalDevice()->GetPhysicalDevice().GetMemoryProperties();
	uint32_t memoryTypeIndex;
	for (memoryTypeIndex=0; memoryTypeIndex<memoryProperties.size(); memoryTypeIndex++)
	{
		if (memRequirements.memoryTypeBits & (1 << memoryTypeIndex))
		{
			if ((memoryProperties[memoryTypeIndex].MemFlags & flags) == flags)
			{
				break;
			}
		}
	}






	MemoryHandle memHandle = this->Allocate(memoryTypeIndex, memRequirements.alignment, memRequirements.size);
	memHandle.BindBuffer(buffer);

	return memHandle;

}


void VulkanMemoryBlock::BindBuffer(VkBuffer bhandle) const
{
	vkBindBufferMemory(_chunk->_parent->GetLogicalDevice()->GetHandle(), bhandle, _chunk->_memoryHandle, this->AlignedOff);
}

void VulkanMemoryBlock::Free()
{
	IsFree = true;
	AlignedOff = Off;
	Size = TotalSize;
	AlignedOff = 0;
	this->_chunk->ComputeFreeBlocksSize();
}

uint64_t VulkanMemoryBlock::GetOffset() const
{
	return AlignedOff;
}
