#pragma once
#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include <vector>

class VulkanLogicalDevice;

class VulkanDescriptorSetLayout
{
	friend class VulkanDescriptorSetPool;

	VkDescriptorSetLayout _handle;
	VulkanLogicalDevice *_dev;
	std::vector<IVulkanRenderSlot*> _slots;
	;
public:
	VulkanDescriptorSetLayout(VulkanLogicalDevice* device, const std::vector<IVulkanRenderSlot*> &v);
	VkDescriptorSetLayout GetHandle() const { return _handle; }
	~VulkanDescriptorSetLayout();
	std::vector<IVulkanRenderSlot*> GetSlots() { return _slots; };
};

