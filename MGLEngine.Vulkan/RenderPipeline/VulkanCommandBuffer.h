#pragma once
#include "VulkanCommandPool.h"

class VulkanCommandBuffer
{
	const VulkanCommandPool& _pool;
	VkCommandBuffer _vkCommandBuffer;
public:
	VulkanCommandBuffer();
	VulkanCommandBuffer(const VulkanCommandPool& pool);
	~VulkanCommandBuffer();
};

