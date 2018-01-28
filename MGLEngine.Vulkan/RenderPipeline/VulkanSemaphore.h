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
	VulkanSemaphore(const VulkanLogicalDevice* logicalDevice);
	
	VulkanSemaphore & operator=(const VulkanSemaphore&) = delete;
	VulkanSemaphore(const VulkanSemaphore&) = delete;

	~VulkanSemaphore();
	VkSemaphore GetHandle() const { assert(_logicalDevice); return _vkSemaphore; }
};

