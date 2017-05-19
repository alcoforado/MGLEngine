#pragma once
#include "VulkanContext/AllocatedQueue.h"
#include <cstdint>
class VulkanLogicalDevice;

class VulkanSemaphore
{
	VkSemaphore _vkSemaphore;
	const VulkanLogicalDevice& _logicalDevice;
public:
	VulkanSemaphore(const VulkanLogicalDevice & logicalDevice);
	~VulkanSemaphore();
};

