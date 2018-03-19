#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderResource.h"
#include <vector>

class VulkanLogicalDevice;
class VulkanDescriptorSetPool;
class VulkanDescriptorSet
{
	friend class VulkanDescriptorSetPool;
	
	VkDescriptorSet _dsHandle;
	VkDescriptorSetLayout _handle;
	VulkanLogicalDevice *_dev;
	std::vector<IVulkanRenderResource*> _resources;
	void SetDescriptorSetHandle(VkDescriptorSet dsHandle) { _dsHandle = dsHandle; }
	~VulkanDescriptorSet();
public:
	VulkanDescriptorSet(VulkanLogicalDevice* device, const std::vector<IVulkanRenderResource*> &v);
	VkDescriptorSetLayout GetLayoutHandle() const { return _handle; }
	VkDescriptorSet GetDescriptorSetHandle() const { return _dsHandle; }
};

