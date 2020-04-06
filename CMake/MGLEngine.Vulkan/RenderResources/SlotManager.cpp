#include "SlotManager.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetLayout.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetPool.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h>

/*
 * The Slot Manager
 */



SlotManager::LayoutData& SlotManager::GetLayoutData(std::string name)
{
	for (auto& ld : _data)
	{
		if (ld.pLayout->GetName() == name)
			return ld;
	}
	throw std::exception("Layout not found ");
}

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


void SlotManager::RegisterDescriptorSetLayout(std::string name,std::vector<IVulkanRenderSlot*> slots)
{
	eassert(std::includes(_allSlots.begin(), _allSlots.end(), slots.begin(), slots.end()), "One or more slots passed do not belong to the actually pipeline");
	eassert(!IsLoaded(),"Cannot add more layouts to the pipeline because it is already loaded")
	LayoutData ld;
	ld.pLayout = new VulkanDescriptorSetLayout(_pDev,name,slots);
	_data.push_back(ld);

	
}

std::vector<VulkanDescriptorSet*> SlotManager::AllocateDescritorSets(std::string  layoutName, int descriptorSetsCount)
{
	std::vector<VulkanDescriptorSet*> r;
	SlotManager::LayoutData& data = GetLayoutData(layoutName);
	for(int i=0;i<descriptorSetsCount;i++)
	{
		VulkanDescriptorSet *p=new VulkanDescriptorSet(data.pLayout);
		data.vDescSets.push_back(p);
		r.push_back(p);
	}
	return r;
	
}



VulkanDescriptorSet* SlotManager::GetDescriptorSet(int iLayout, int iDescSet)
{
	eassert(iLayout < _data.size(), "Error layoutNumber " << iLayout << " out of range [0," << _data.size() - 1);
	eassert(iDescSet < _data[iLayout].vDescSets.size(), "Error descriptor set index out of range");
	return _data[iLayout].vDescSets[iDescSet];

}


VulkanDescriptorSet* SlotManager::GetDescriptorSet(std::string layoutName, int iDescSet)
{
	SlotManager::LayoutData ld = GetLayoutData(layoutName);
	eassert(iDescSet < ld.vDescSets.size(), "Error descriptor set index out of range");
	return ld.vDescSets[iDescSet];

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
