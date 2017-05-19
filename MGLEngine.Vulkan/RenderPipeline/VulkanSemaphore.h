#pragma once
#include <cstdint>
#include <vulkan/vulkan.h>

class VulkanLogicalDevice;

class VulkanSemaphore
{
	VkSemaphore _vkSemaphore;
	const VulkanLogicalDevice& _logicalDevice;
public:
	VulkanSemaphore(const VulkanLogicalDevice & logicalDevice);
	~VulkanSemaphore();
	VkSemaphore GetHandle() const { return _vkSemaphore; }
};

