#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include "VulkanDescriptorSetLayout.h"
#include "VulkanDescriptorSet.h"
#include <MGLEngine.Shared/Utils/opointer.h>
#include <algorithm>
class VulkanPipeline;
class SlotManager
{
	std::vector<IVulkanRenderSlot*> _allSlots;
	const VulkanLogicalDevice *_pDev;
	VulkanPipeline* _pPipeline;

private:
	struct LayoutData
	{
		OPointer<VulkanDescriptorSetLayout> pLayout;
		std::vector<VulkanDescriptorSet*> vDescSets;

	};

	std::vector<LayoutData> _data;

public:
	SlotManager(VulkanPipeline *pipeline, std::vector<IVulkanRenderSlot*> allSlots);
	void AddLayout(std::vector<IVulkanRenderSlot*> slots);
	void AllocateDescritorSets(int layoutNumber, int descriptorSetsCount);
	VulkanDescriptorSet* GetDescriptorSet(int iLayout, int iDescSet);

	void OnCommandBufferOpen(VulkanCommandBuffer *cb, int frameIndex);
	void OnFrameStart(int iFrame);
	~SlotManager();
	std::vector<VulkanDescriptorSetLayout*> GetDescriptorSetLayouts(); 
};


