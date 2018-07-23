#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include "VulkanDescriptorSetLayout.h"
#include "VulkanDescriptorSet.h"

class SlotManager
{
	std::vector<IVulkanRenderSlot*> _slots;
	VulkanLogicalDevice *_pDev;
	VulkanDescriptorSetLayout* _pLayout;
	void SetStrategyToOneDescriptorSetPerFrame(int nFrames);

private:
	struct FrameData
	{
		VulkanDescriptorSet* DescriptorSet;
		
	};
	
	
public:
	SlotManager(VulkanLogicalDevice *dev,std::vector<IVulkanRenderSlot*> resources,int nFrames);

	~SlotManager();
};

