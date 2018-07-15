#pragma once
#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderResource.h"
#include <vector>

class VulkanDescriptorSetLayout
{
	friend class VulkanDescriptorSetPool;

	VkDescriptorSetLayout _handle;
	VulkanLogicalDevice *_dev;
	std::vector<IVulkanRenderResource*> _resources;
	;
public:
	VulkanDescriptorSetLayout(VulkanLogicalDevice* device, const std::vector<IVulkanRenderResource*> &v);
	VkDescriptorSetLayout GetLayoutHandle() const { return _handle; }
	~VulkanDescriptorSetLayout();
};

