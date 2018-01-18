#pragma once
#include "../VulkanContext/VulkanAllocatedQueue.h"
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
class VulkanCommandBufferOptions;
class VulkanLogicalDevice;
class VulkanCommandBuffer;
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

	VulkanCommandBuffer* CreateCommandBuffer(VulkanCommandBufferOptions options);
};

