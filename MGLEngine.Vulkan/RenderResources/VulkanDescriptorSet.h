#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include <vector>

class VulkanLogicalDevice;
class VulkanDescriptorSetPool;
class VulkanDescriptorSet
{
	friend class VulkanDescriptorSetPool;
	
	VkDescriptorSet _dsHandle;
	VkDescriptorSetLayout _handle;
	VulkanLogicalDevice *_dev;
	std::vector<IVulkanRenderSlot*> _resources;
	void SetDescriptorSetHandle(VkDescriptorSet dsHandle) { _dsHandle = dsHandle; }
	VulkanDescriptorSet(VulkanLogicalDevice* device, const std::vector<IVulkanRenderSlot*> &v);
	~VulkanDescriptorSet();
public:
	VkDescriptorSetLayout GetLayoutHandle() const { return _handle; }
	VkDescriptorSet GetDescriptorSetHandle() const { return _dsHandle; }
};

