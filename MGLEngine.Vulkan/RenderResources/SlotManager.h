#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include "VulkanDescriptorSetLayout.h"

class SlotManager
{
	std::vector<IVulkanRenderSlot*> _slots;
	VulkanLogicalDevice *_pDev;
	VulkanDescriptorSetLayout* _pLayout;
public:
	SlotManager(VulkanLogicalDevice *dev,std::vector<IVulkanRenderSlot*> resources);
	~SlotManager();
};

