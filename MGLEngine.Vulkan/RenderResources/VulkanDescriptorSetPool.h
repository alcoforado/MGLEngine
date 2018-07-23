#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanDescriptorSetLayout;
class VulkanLogicalDevice;
class VulkanDescriptorSet;
class IVulkanRenderSlot;
struct PoolAllocation
{
	unsigned int UniformBuffers;
};

class VulkanDescriptorSetPool
{
	VkDescriptorPool _handle;
	PoolAllocation _alloc;
	VulkanLogicalDevice *_dev;
	std::vector<VulkanDescriptorSet*> _descriptorSets;
public:
	VulkanDescriptorSetPool(VulkanLogicalDevice *dev);
	~VulkanDescriptorSetPool();

	VulkanDescriptorSet * CreateDescriptorSet(VulkanDescriptorSetLayout * pLayout);

	VkDescriptorPool GetHandle() const { return _handle; }

	void AllocateDescriptorSets();
	bool IsAllocated();
};

