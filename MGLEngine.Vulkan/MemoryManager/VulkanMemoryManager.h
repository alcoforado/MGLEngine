#pragma once
#include "../RenderPipeline/CommandBufferCollection.h"
#include <list>

class IBinding
{
	VkBuffer _buffer;
};

class VulkanMemoryBlock
{
public:
	uint64_t Off;
	uint64_t AlignedOff;
	uint64_t Size;
	bool IsFree;
	VulkanMemoryBlock(uint64_t lOff, uint64_t lAlignedOff, uint64_t lSize, bool lIsFree)
	{
		this->Off = lOff;
		this->AlignedOff = lAlignedOff;
		this->Size = lSize;
		this->IsFree = lIsFree;
	};
	
	
	//IBinding Resource;
};

class VulkanMemoryManager;
class VulkanMemoryChunk
{
	friend class VulkanMemoryManager;
	uint64_t _totalFree;
	uint64_t _size;
	uint64_t _maxBlockSize;
	VulkanMemoryBlock *_pBiggestBlock;
	std::list<VulkanMemoryBlock*> _blocks;
	uint32_t MemoryTypeIndex;
	explicit VulkanMemoryChunk(uint32_t memoryTypeIndex,uint64_t size);
	bool TryToAllocate(uint32_t memoryIndex, uint32_t alignment, uint64_t size);
};


class VulkanMemoryManager
{
	uint64_t _blockSize;
	std::list<VulkanMemoryChunk*> _chunks;
	VulkanLogicalDevice &_device;
public:
	VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeMB);
	~VulkanMemoryManager();
	void Allocate(uint32_t memoryIndex, uint32_t alignment, uint64_t size);
};

