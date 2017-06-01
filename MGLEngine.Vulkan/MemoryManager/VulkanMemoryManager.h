#pragma once
#include "../RenderPipeline/CommandBufferCollection.h"
#include <list>

class IBinding
{
	VkBuffer _buffer;
};
class VulkanMemoryChunk;



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


public:

	VulkanMemoryBlock(VulkanMemoryChunk *chunk,uint64_t lOff, uint64_t lSize)
	{
		this->Off = lOff;
		this->AlignedOff = this->Off;
		this->Size = lSize;
		this->_chunk = chunk;
		this->TotalSize = lSize;
		this->AlignmentOffset = 0;
		this->IsFree = true;
	};
	
	
	//IBinding Resource;
};

typedef VulkanMemoryBlock MemoryHandle;

class VulkanMemoryManager;
class VulkanMemoryChunk
{
	friend class VulkanMemoryManager;
	uint64_t _totalFree;
	uint64_t _size;
	uint64_t _maxBlockSize;
	VulkanMemoryBlock *_pBiggestBlock;
	std::list<VulkanMemoryBlock*> _blocks;
	VkMemoryAllocateInfo _allocInfo;
	VkDeviceMemory _memoryHandle;

	VulkanMemoryManager *_parent;


	explicit VulkanMemoryChunk(VulkanMemoryManager *parent, uint32_t memoryTypeIndex, uint64_t size);
	void ComputeFreeBlocksSize();
	bool TryToAllocate(uint32_t memoryTypeIndex, uint32_t alignment, uint64_t size);
};


class VulkanMemoryManager
{
	uint64_t _blockSize;
	std::list<VulkanMemoryChunk*> _chunks;
	const VulkanLogicalDevice &_device;
public:
	VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeMB);
	~VulkanMemoryManager();
	const VulkanLogicalDevice& GetLogicalDevice() const { return _device; }
	void Allocate(uint32_t memoryIndex, uint32_t alignment, uint64_t size);
};

