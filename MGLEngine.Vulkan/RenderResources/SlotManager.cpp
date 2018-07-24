#include "SlotManager.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetLayout.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetPool.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
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


SlotManager::~SlotManager()
{
}
