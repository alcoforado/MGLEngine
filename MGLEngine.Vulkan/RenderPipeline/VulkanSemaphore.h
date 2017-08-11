#pragma once
#include <cstdint>
#include <vulkan/vulkan.h>
#include <assert.h>
class VulkanLogicalDevice;

class VulkanSemaphore
{
	VkSemaphore _vkSemaphore;
	const VulkanLogicalDevice* _logicalDevice;
public:
	VulkanSemaphore(const VulkanLogicalDevice & logicalDevice);
	VulkanSemaphore()
	{
		_logicalDevice = nullptr;
		_vkSemaphore = VK_NULL_HANDLE;

	}
	~VulkanSemaphore();
	VkSemaphore GetHandle() const { assert(_logicalDevice); return _vkSemaphore; }
};

