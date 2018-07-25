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
	std::vector<FrameData> _frames;
	
public:
	SlotManager(VulkanLogicalDevice *dev,std::vector<IVulkanRenderSlot*> resources,int nFrames);
	void OnCommandBufferOpen(VulkanCommandBuffer *cb, int frameIndex);
	VulkanDescriptorSet* GetActiveDescriptorSetForFrame(int frameIndex);
	void OnFrameStart(int iFrame);
	
	~SlotManager();
};

