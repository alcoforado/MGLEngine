#pragma once
#include <vulkan/vulkan.h>

class VulkanLogicalDevice;


struct PoolAllocation
{
	unsigned int UniformBuffers;
};

class VulkanDescriptorSetPool
{
	VkDescriptorPool _handle;
	PoolAllocation _alloc;
	VulkanLogicalDevice *_dev;
public:
	VulkanDescriptorSetPool(VulkanLogicalDevice *dev,PoolAllocation alloc);
	~VulkanDescriptorSetPool();

	VkDescriptorPool GetHandle() const { return _handle; }

};

