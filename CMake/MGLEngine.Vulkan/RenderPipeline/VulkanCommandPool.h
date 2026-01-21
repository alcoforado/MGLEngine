#pragma once
#include "../VulkanContext/VulkanQueue.h"
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
public:
	
	~VulkanCommandPool();
	VulkanCommandPool(const VulkanLogicalDevice &_device);
	VkCommandPool GetHandle() const { return _vkPool; }
	const VulkanLogicalDevice& GetLogicalDevice() const {
		return _logicalDevice;
	}
	std::unique_ptr<VulkanCommandBuffer> CreateCommandBuffer(VulkanCommandBufferOptions options);
};

