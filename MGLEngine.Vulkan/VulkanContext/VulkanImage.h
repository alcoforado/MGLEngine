#pragma once

#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/vmausage.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryProperties.h>

class VulkanMemoryAllocator;
class VulkanImage {
	VkImage _handle;
	VulkanMemoryAllocator *_pAllocator;
	VkImageCreateInfo _createInfo;
	VmaAllocation _allocation;
	VmaAllocationInfo _allocationInfo;
	VkImageLayout _currentLayout;
	VkFormat _format;
public:
	VulkanImage(VulkanMemoryAllocator* pAllocator, VkImage img, VkImageCreateInfo createInfo, const VmaAllocation& allocation, const VmaAllocationInfo& allocationInfo)
	{
		_pAllocator = pAllocator;
		_handle = img;
		_allocation = allocation;
		_allocationInfo = allocationInfo;
		_createInfo = createInfo;
		_currentLayout = _createInfo.initialLayout;
		_format = createInfo.format;

	}
	VulkanImage()
	{
		_pAllocator = nullptr;
		_handle = VK_NULL_HANDLE;
		_allocation = {};
		_allocationInfo = {};

	}


	bool IsHostVisible();

	VkImage GetHandle() const {
		return _handle;
	}
	
	VkFormat GetImageFormat() const {
		return _createInfo.format;
	}

	VkImageLayout GetImageLayout() const  {
		return _currentLayout;
	}


	void SetCurrentLayout(VkImageLayout currentLayout) {
		_currentLayout = currentLayout;

	}
private:
	

};
