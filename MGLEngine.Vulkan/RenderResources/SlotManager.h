#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>

class SlotManager
{
public:
	SlotManager(std::vector<IVulkanRenderSlot*> resources);
	~SlotManager();
};

