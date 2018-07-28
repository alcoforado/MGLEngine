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
}

void SlotManager::AddLayout(std::vector<IVulkanRenderSlot*> slots)
{
	eassert(std::includes(_allSlots.begin(), _allSlots.end(), slots.begin(), slots.end()), "One or more slots passed do not belong to the actually pipeline");
	eassert(!_pPipeline->IsLoaded(),"Cannot add more layouts to the pipeline because it is already loaded")
	LayoutData ld;
	ld.pLayout = new VulkanDescriptorSetLayout(_pDev,slots);
	_data.push_back(ld);
}

void SlotManager::AllocateDescritorSets(int layoutNumber, int descriptorSetsCount)
{
	eassert(layoutNumber < _data.size(),"Error layoutNumber " << layoutNumber << " out of range [0," << _data.size()-1);
	for(int i=0;i<descriptorSetsCount;i++)
	{
		_data[layoutNumber].vDescSets.push_back	(
			new VulkanDescriptorSet(_data[layoutNumber].pLayout)
		);
	}
	
}

VulkanDescriptorSet* SlotManager::GetDescriptorSet(int iLayout,int iDescSet)
{
	eassert(iLayout < _data.size(), "Error layoutNumber " << iLayout << " out of range [0," << _data.size() - 1);
	eassert(iDescSet < _data[iLayout].vDescSets.size(), "Error descriptor set index out of range");
	return _data[iLayout].vDescSets[iDescSet];

}


SlotManager::~SlotManager()
{
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
