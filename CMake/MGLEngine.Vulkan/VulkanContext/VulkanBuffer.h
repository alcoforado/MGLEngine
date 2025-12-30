#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
class VulkanBuffer {

public:
	VkBuffer buffer;
	uint32_t size;
	bool isDeviceMemory;
	uint32_t deviceMemoryTypeIndex;
	VkBufferUsageFlags usage;
	VmaAllocation allocation;
	VmaAllocationInfo allocationInfo;
	VulkanBuffer() {}
};