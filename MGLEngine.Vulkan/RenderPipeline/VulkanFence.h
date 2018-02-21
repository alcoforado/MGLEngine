#pragma once
#include <vulkan/vulkan.h>
class VulkanLogicalDevice;
class VulkanFence
{
	VkFence _fence;
	const VulkanLogicalDevice *_dev;
public:

	VulkanFence(const VulkanLogicalDevice *dev,bool b=false);

	~VulkanFence();
	VkFence GetHandle() const { return _fence; }
	void Wait() const;
};

