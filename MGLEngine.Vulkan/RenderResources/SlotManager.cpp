#include "SlotManager.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetLayout.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetPool.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h>

/*
 * The Slot Manager
 */



SlotManager::SlotManager(VulkanPipeline* pipeline, std::vector<IVulkanRenderSlot*> allSlots)
{
	_pDev = pipeline->GetLogicalDevice();
	_allSlots = allSlots;
	_pPipeline = pipeline;
	_vkPipelineLayout = VK_NULL_HANDLE;

	

}

std::vector<IVulkanRenderSlot*> SlotManager::GetSlotsByFrequence(ResourceWriteFrequency freq)
{
	std::vector<IVulkanRenderSlot*> slots;
	for (auto sl : _allSlots)
	{
		if (sl->WriteFrequency() == ResourceWriteFrequency::ONCE_PER_FRAME)
			slots.push_back(sl);
	}
	return slots;
}


int SlotManager::AddLayout(std::vector<IVulkanRenderSlot*> slots)
{
	eassert(std::includes(_allSlots.begin(), _allSlots.end(), slots.begin(), slots.end()), "One or more slots passed do not belong to the actually pipeline");
	eassert(!IsLoaded(),"Cannot add more layouts to the pipeline because it is already loaded")
	LayoutData ld;
	ld.pLayout = new VulkanDescriptorSetLayout(_pDev,slots);
	_data.push_back(ld);

	return static_cast<int>(_data.size() - 1);
}

void SlotManager::AllocateDescritorSets(int layoutNumber, int descriptorSetsCount)
{
	eassert(layoutNumber < _data.size(),"Error layoutNumber " << layoutNumber << " out of range [0," << _data.size()-1);
	for(int i=0;i<descriptorSetsCount;i++)
	{
		_data[layoutNumber].vDescSets.push_back	(new VulkanDescriptorSet(_data[layoutNumber].pLayout));
	}
	
}



VulkanDescriptorSet* SlotManager::GetDescriptorSet(int iLayout,int iDescSet)
{
	eassert(iLayout < _data.size(), "Error layoutNumber " << iLayout << " out of range [0," << _data.size() - 1);
	eassert(iDescSet < _data[iLayout].vDescSets.size(), "Error descriptor set index out of range");
	return _data[iLayout].vDescSets[iDescSet];

}

void SlotManager::Load()
{
	eassert(!IsLoaded(), "Error slotmanager is already loaded");

	//Create Layout
	VkPipelineLayoutCreateInfo PipelineLayoutInfo = {};
	PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	PipelineLayoutInfo.setLayoutCount = 0; // Optional
	PipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	PipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	PipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

	std::vector<VkDescriptorSetLayout> vkDescriptorSetsLayout;
	for (auto d : GetDescriptorSetLayouts())
	{
		vkDescriptorSetsLayout.push_back(d->GetHandle());
	}
	PipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(vkDescriptorSetsLayout.size());
	PipelineLayoutInfo.pSetLayouts = vkDescriptorSetsLayout.size()>0 ? vkDescriptorSetsLayout.data() : nullptr;

	auto err = vkCreatePipelineLayout(_pDev->GetHandle(), &PipelineLayoutInfo, nullptr, &_vkPipelineLayout);
	AssertVulkanSuccess(err);
}


SlotManager::~SlotManager()
{
	for (auto d : _data)
	{
		delete d.pLayout;
	}
	vkDestroyPipelineLayout(_pDev->GetHandle(), _vkPipelineLayout, nullptr);
}

std::vector<VulkanDescriptorSetLayout*> SlotManager::GetDescriptorSetLayouts()
{
	std::vector<VulkanDescriptorSetLayout*> result;
	for (auto d: _data)
	{
		result.push_back(d.pLayout);
	}
	return result;
}

VkPipelineLayout SlotManager::GetVkPipelineLayoutHandle() const
{
	eassert(this->IsLoaded(), "SlotManager not yet loaded, VkPipelineLLayout is not available yet");
	return _vkPipelineLayout;
}
