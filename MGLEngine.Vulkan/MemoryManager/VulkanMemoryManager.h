#pragma once
#include "../RenderPipeline/CommandBufferCollection.h"

class IBinding
{
	VkBuffer _buffer;
};

class VulkanMemoryBlock
{
public:
	long Off;
	long Size;
	bool IsFree;
	IBinding Resource;
};


class VulkanMemoryChunk
{
	long _totalFree;
	long _size;
	VulkanMemoryBlock *_maxBlockSize;


};


class VulkanMemoryManager
{
	int _blockSize;
	VulkanLogicalDevice &_device;
public:
	VulkanMemoryManager(VulkanLogicalDevice& device, int blockSize);
	~VulkanMemoryManager();
};

