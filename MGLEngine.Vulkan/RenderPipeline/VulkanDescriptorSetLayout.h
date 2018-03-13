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
	VulkanDescriptorSetLayout(VulkanLogicalDevice* device, const std::vector<IVulkanRenderResource*> &v);
	~VulkanDescriptorSetLayout();
	VkDescriptorSetLayout GetHandle() const { return _handle; }
};

