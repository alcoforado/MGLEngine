#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
class VulkanBuffer {
	bool IsDeviceMemory();
	bool IsHostVisible();
public:
	VkBuffer buffer;
	uint32_t size;
	bool isDeviceMemory;
	bool isHostVisible;
	VulkanMemoryProperties memType;
	uint32_t deviceMemoryTypeIndex;
	VkBufferUsageFlags usage;
	VmaAllocation allocation;
	VmaAllocationInfo allocationInfo;
	

};