#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include "VulkanDescriptorSetLayout.h"
#include "VulkanDescriptorSet.h"
#include <MGLEngine.Shared/Utils/opointer.h>
#include <algorithm>
class VulkanPipeline;
class SlotManager
{
	friend class VulkanPipeline;
	std::vector<IVulkanRenderSlot*> _allSlots;
	const VulkanLogicalDevice *_pDev;
	VulkanPipeline* _pPipeline;
	VkPipelineLayout _vkPipelineLayout;


private:
	struct LayoutData
	{
		VulkanDescriptorSetLayout *pLayout;
		std::vector<VulkanDescriptorSet*> vDescSets;

	};

	std::vector<LayoutData> _data;

public:
	SlotManager(VulkanPipeline *pipeline, std::vector<IVulkanRenderSlot*> allSlots);
	std::vector<IVulkanRenderSlot*> GetSlotsByFrequence(ResourceWriteFrequency freq);
	int AddLayout(std::vector<IVulkanRenderSlot*> slots);
	void AllocateDescritorSets(int layoutNumber, int descriptorSetsCount);
	VulkanDescriptorSet* GetDescriptorSet(int iLayout, int iDescSet);
	void Load();
	void OnCommandBufferOpen(VulkanCommandBuffer *cb, int frameIndex);
	void OnFrameStart(int iFrame);
	~SlotManager();
	bool IsLoaded() const {
		return _vkPipelineLayout != VK_NULL_HANDLE;
	}
	std::vector<VulkanDescriptorSetLayout*> GetDescriptorSetLayouts(); 
	VkPipelineLayout GetVkPipelineLayoutHandle() const;

};



