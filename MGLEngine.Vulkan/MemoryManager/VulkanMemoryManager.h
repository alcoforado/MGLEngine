#pragma once
#include <list>
#include "Utils/Arrays/IArray.h"
#include <vulkan/vulkan.h>

class VulkanMemoryBlock;
class VulkanMemoryChunk;
class VulkanLogicalDevice;

//typedef const VulkanMemoryBlock* MemoryHandle;

class MemoryHandle
{
	friend class VulkanMemoryManager;
	VulkanMemoryBlock *_block;
	void BindBuffer(VkBuffer buff) const;

public:
	MemoryHandle(VulkanMemoryBlock *block=nullptr)
	{
		_block = block;
	}
	void Free();
	uint64_t GetOffset() const;
	
	template<class T>
	IArray<T> Map(uint64_t nElems)
	{
		return _block->Map<T>(nElems);
	}

};


class VulkanMemoryManager
{

	uint64_t _blockSize;
	std::list<VulkanMemoryChunk*> _chunks;
	const VulkanLogicalDevice &_device;
	MemoryHandle VulkanMemoryManager::Allocate(uint32_t memoryTypeIndex, uint64_t alignment, uint64_t size);
public:
	VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeMB);
	~VulkanMemoryManager();
	const VulkanLogicalDevice& GetLogicalDevice() const { return _device; }
	MemoryHandle VulkanMemoryManager::Allocate(VkBuffer buffer, std::vector<enum VkMemoryPropertyFlagBits> flags);
};





class VulkanMemoryChunk
{
	friend class VulkanMemoryBlock;
	friend class VulkanMemoryManager;
	uint64_t _totalFree;
	uint64_t _size;
	uint64_t _maxBlockSize;
	VulkanMemoryBlock *_pBiggestBlock;
	std::list<VulkanMemoryBlock*> _blocks;
	VkMemoryAllocateInfo _allocInfo;
	VkDeviceMemory _memoryHandle;
	bool _isMapped;
	char* _data;
	VulkanMemoryManager *_parent;


	explicit VulkanMemoryChunk(VulkanMemoryManager *parent, uint32_t memoryTypeIndex, uint64_t size);
	void ComputeFreeBlocksSize();
	VulkanMemoryBlock* TryToAllocate(uint32_t memoryTypeIndex, uint64_t alignment, uint64_t size);
	void Map();
};




class VulkanMemoryBlock
{
	friend class VulkanMemoryChunk;

	uint64_t Off;
	uint64_t AlignedOff;
	uint64_t TotalSize;
	uint64_t Size;
	bool IsFree;
	uint64_t AlignmentOffset;
	VulkanMemoryChunk *_chunk;

	VulkanMemoryBlock(VulkanMemoryChunk *chunk, uint64_t lOff, uint64_t lSize)
	{
		this->Off = lOff;
		this->AlignedOff = this->Off;
		this->Size = lSize;
		this->_chunk = chunk;
		this->TotalSize = lSize;
		this->AlignmentOffset = 0;
		this->IsFree = true;
	};


public:
	template<class T>
	IArray<T> Map(uint64_t nElems)
	{
		assert(!IsFree);
		_chunk->Map();
		assert(nElems <= Size / sizeof(T));
		return IArray<T>(reinterpret_cast<T*>(_chunk->_data + AlignedOff),nElems,Size/sizeof(T));
	}

	void BindBuffer(VkBuffer uint64) const;
	void Free();
	uint64_t GetOffset() const;

	//IBinding Resource;
};


extern const int _MB; 


