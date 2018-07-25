#include "SlotManager.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetLayout.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetPool.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>
/*
 * The Slot Manager
 */

SlotManager::SlotManager(VulkanLogicalDevice *pDev,std::vector<IVulkanRenderSlot*> resources,int nFrames)
{
	_slots = resources;
	_pDev = pDev;

	_pLayout = new VulkanDescriptorSetLayout(pDev, _slots);


	for (int i=0;i<nFrames;i++)
	{
		VulkanDescriptorSet* pSet = pDev->GetDescriptorSetPool()->CreateDescriptorSet(_pLayout);
		_frames.push_back({ pSet });
	}
}

VulkanDescriptorSet* SlotManager::GetActiveDescriptorSetForFrame(int frameIndex)
{
	return _frames[frameIndex].DescriptorSet;
}

void SlotManager::OnFrameStart(int iFrame)
{
	//Update all bindings related to DescriptorSet assigned to a frame
	for(auto pBind : _frames[iFrame].DescriptorSet->GetBindings())
	{
		pBind->Update();
	}
}



SlotManager::~SlotManager()
{
}
