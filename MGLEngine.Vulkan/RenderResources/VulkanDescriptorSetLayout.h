#pragma once
#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include <vector>

class VulkanLogicalDevice;

class VulkanDescriptorSetLayout
{
	friend class VulkanDescriptorSetPool;

	VkDescriptorSetLayout _handle;
	const VulkanLogicalDevice *_dev;
	std::vector<IVulkanRenderSlot*> _slots;
	;
public:
	VulkanDescriptorSetLayout(const VulkanLogicalDevice* device, const std::vector<IVulkanRenderSlot*> &v);
	VkDescriptorSetLayout GetHandle() const { return _handle; }
	~VulkanDescriptorSetLayout();
	const VulkanLogicalDevice* GetVulkanLogicalDevice() const { return _dev; }
	std::vector<IVulkanRenderSlot*> GetSlots() { return _slots; };
};

