#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderResource.h"
#include <vector>
#include "VulkanInputLayout.h"

class VulkanLogicalDevice;

class VulkanDescriptorSetLayout
{
	VkDescriptorSetLayout _handle;
	VulkanLogicalDevice *_dev;
public:
	VulkanDescriptorSetLayout(VulkanLogicalDevice* device, std::vector<IVulkanRenderResource*> &v);
	~VulkanDescriptorSetLayout();
};

