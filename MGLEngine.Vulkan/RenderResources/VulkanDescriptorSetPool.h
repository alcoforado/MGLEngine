#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanLogicalDevice;
class VulkanDescriptorSet;
class IVulkanRenderResource;
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

	VkDescriptorPool GetHandle() const { return _handle; }

	VulkanDescriptorSet* CreateDescriptorSet(const std::vector<IVulkanRenderResource*> &v);
	void AllocateDescriptorSets();
	bool IsAllocated();
};

