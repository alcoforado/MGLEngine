#include "VulkanMemoryManager.h"
#include <algorithm>


VulkanMemoryChunk::VulkanMemoryChunk(uint32_t memoryTypeIndex,uint64_t size)
{

}

bool VulkanMemoryChunk::TryToAllocate(uint32_t memoryIndex, uint32_t alignment,uint64_t size)
{
	for (auto block : _blocks)
	{
		uint64_t rest = (alignment - block->Off%alignment) % alignment;
		if (block->IsFree && block->Size>=size+rest)
		{
			block->AlignedOff = block->Off + rest;
			block->IsFree = false;
			if (block->Size > size + rest)
			{
				auto newBlock = new VulkanMemoryBlock(block->AlignedOff + size, std::numeric_limits<uint64_t>::max(), block->Size - size - rest, true);
				this->_blocks.push_back(newBlock);
			}
			if (block == _pBiggestBlock)
			{
			this->ComputeMaxFreeBlockSize();
				
			}

		}

	}
	return true;
}

VulkanMemoryManager::VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeMB)
:_device(device)
{
	_blockSize = blockSizeMB* 1048576;
}


VulkanMemoryManager::~VulkanMemoryManager()
{
}

void VulkanMemoryManager::Allocate(uint32_t memoryIndex, uint32_t alignment, uint64_t size)
{
	assert(memoryIndex < _device.GetPhysicalDevice().GetMemoryProperties().size());
	for (VulkanMemoryChunk *chunk : _chunks)
	{
		if (size <= chunk->_maxBlockSize && chunk->MemoryTypeIndex == memoryIndex)
		{
			if (chunk->TryToAllocate(memoryIndex, alignment, size))
			{
				return;
			}
		}
	}

	//
	_chunks.push_back(new VulkanMemoryChunk(memoryIndex,std::max(_blockSize, size)));


}
