#pragma once
#include <vulkan/vulkan.h>
class VulkanLogicalDevice;
class VulkanFence
{
	VkFence _fence;
	VulkanLogicalDevice *_dev;
public:

	VulkanFence(VulkanLogicalDevice *dev);

	~VulkanFence();
	VkFence GetHandle() { return _fence; }
};

