#pragma once
#include "../VulkanContext/AllocatedQueue.h"
class VulkanLogicalDevice;

class VulkanCommandPool
{
	const VulkanLogicalDevice& _logicalDevice;
	VkCommandPool _vkPool;
public:
	explicit VulkanCommandPool(const VulkanLogicalDevice &_device);
	~VulkanCommandPool();
	VkCommandPool GetHandle() const { return _vkPool; }
	const VulkanLogicalDevice& GetLogicalDevice() const {
		return _logicalDevice;
	}
};

