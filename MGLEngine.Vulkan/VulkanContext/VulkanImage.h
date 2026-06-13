#pragma once

#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/vmausage.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryProperties.h>

class VulkanMemoryAllocator;
class VulkanCommandBuffer;
class VulkanImage {
	VkImage _handle;
	VulkanMemoryAllocator *_pAllocator;
	VkImageCreateInfo _createInfo;
	VmaAllocation _allocation;
	VmaAllocationInfo _allocationInfo;
	VkImageLayout _currentLayout;
	VkFormat _format;
	VkDeviceSize _sizeInBytes; 
	VkAccessFlags _accessFlags;

	void AssertIsNotDeleted() const;
public:
	VulkanImage(VulkanMemoryAllocator* pAllocator, VkImage img, VkImageCreateInfo createInfo, const VmaAllocation& allocation, const VmaAllocationInfo& allocationInfo);
	
	VulkanImage()
	{
		_pAllocator = nullptr;
		_handle = VK_NULL_HANDLE;
		_allocation = {};
		_allocationInfo = {};

	}


	bool IsHostVisible();

	VkImage GetHandle() const {
		AssertIsNotDeleted();
		return _handle;
	}
	
	VkFormat GetImageFormat() const {
		AssertIsNotDeleted();
		return _createInfo.format;
	}

	VkImageLayout GetCurrentImageLayout() const  {
		AssertIsNotDeleted();
		return _currentLayout;
	}

	VkExtent3D GetExtent() const {
		return _createInfo.extent;
	}

	VkDeviceSize GetSizeInBytes() const {
		AssertIsNotDeleted();
		return _sizeInBytes;
	}

	static VkDeviceSize GetTexelSize(VkFormat format);

	
	VkAccessFlags GetCurrentAccessMask() {
		AssertIsNotDeleted();
		return _accessFlags;
	}

	void Delete();

private:
	friend class VulkanCommandBuffer;
	void SetCurrentLayout(VkImageLayout currentLayout) {
		AssertIsNotDeleted();
		_currentLayout = currentLayout;

	}
	void SetCurrentAccessMask(VkAccessFlags accessFlags)
	{
		AssertIsNotDeleted();
		_accessFlags = accessFlags;
	}

	
	

};
