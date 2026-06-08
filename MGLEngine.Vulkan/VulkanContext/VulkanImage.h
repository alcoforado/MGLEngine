#pragma once

#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/vmausage.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryProperties.h>

class VulkanMemoryAllocator;
class VulkanImage {
	VkImage _handle;
	VulkanMemoryAllocator *_pAllocator;
	VmaAllocation _allocation;
	VmaAllocationInfo _allocationInfo;
public:
	VulkanImage(VulkanMemoryAllocator* pAllocator, VkImage img, const VmaAllocation& allocation, const VmaAllocationInfo& allocationInfo)
	{
		_pAllocator = pAllocator;
		_handle = img;
		_allocation = allocation;
		_allocationInfo = allocationInfo;

	}
	VulkanImage()
	{
		_pAllocator = nullptr;
		_handle = VK_NULL_HANDLE;
		_allocation = {};
		_allocationInfo = {};

	}

	bool IsHostVisible();


private:


};
