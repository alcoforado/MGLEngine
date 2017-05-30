#pragma once
#include "CommandBufferCollection.h"
class VulkanLogicalDevice;

class VulkanStagingBuffer
{
	VkDeviceMemory _memoryHandle;
	VulkanLogicalDevice&  _device;
	VkBuffer _handle;
	long _size;
	void AllocBuffer(VulkanLogicalDevice &device, long size);
public:
	VulkanStagingBuffer(VulkanLogicalDevice &device,long size);
	~VulkanStagingBuffer();
	void clear();

	void resize(size_t size);
	

};

