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
	uint64_t Size;
	bool IsFree;
	IBinding Resource;
};

class VulkanMemoryManager;
class VulkanMemoryChunk
{
	friend class VulkanMemoryManager;
	uint64_t _totalFree;
	uint64_t _size;
	uint64_t _maxBlockSize;
	std::list<VulkanMemoryBlock> _blocks;
	VulkanMemoryChunk();
};


class VulkanMemoryManager
{
	uint64_t _blockSize;
	std::list<VulkanMemoryChunk*> _chunks;
	VulkanLogicalDevice &_device;
public:
	VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeMB);
	~VulkanMemoryManager();
	void Allocate(uint64_t size);
};

