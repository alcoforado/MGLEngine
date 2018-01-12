#pragma once
#include "../VulkanContext/VulkanAllocatedQueue.h"
class VulkanLogicalDevice;

class VulkanCommandPool 
{
	friend class VulkanLogicalDevice;
	const VulkanLogicalDevice& _logicalDevice;
	VkCommandPool _vkPool;
	explicit VulkanCommandPool(const VulkanLogicalDevice &_device);
public:
	
	~VulkanCommandPool();
	VkCommandPool GetHandle() const { return _vkPool; }
	const VulkanLogicalDevice& GetLogicalDevice() const {
		return _logicalDevice;
	}
};

