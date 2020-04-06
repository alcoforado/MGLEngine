#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include "VulkanDescriptorSetLayout.h"
#include "VulkanDescriptorSet.h"
#include <MGLEngine.Shared/Utils/opointer.h>
#include <algorithm>
#include <string>
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
		VulkanDescriptorSetLayout *pLayout;                  //The descreiptorset layout
		std::vector<VulkanDescriptorSet*> vDescSets;         //DescriptorSets allocated havin pLayout as their layout

	};

	std::vector<LayoutData> _data;
	LayoutData& GetLayoutData(std::string name);

public:
	SlotManager(VulkanPipeline *pipeline, std::vector<IVulkanRenderSlot*> allSlots);
	std::vector<IVulkanRenderSlot*> GetSlotsByFrequence(ResourceWriteFrequency freq);
	void RegisterDescriptorSetLayout(std::string name, std::vector<IVulkanRenderSlot*> slots);
	std::vector<VulkanDescriptorSet*>  AllocateDescritorSets(std::string layoutName, int descriptorSetsCount);
	VulkanDescriptorSet* GetDescriptorSet(int iLayout, int iDescSet);
	VulkanDescriptorSet* GetDescriptorSet(std::string layoutName, int iDescSet);

	void Load();
	~SlotManager();
	bool IsLoaded() const {
		return _vkPipelineLayout != VK_NULL_HANDLE;
	}
	std::vector<VulkanDescriptorSetLayout*> GetDescriptorSetLayouts(); 
	VkPipelineLayout GetVkPipelineLayoutHandle() const;

};



