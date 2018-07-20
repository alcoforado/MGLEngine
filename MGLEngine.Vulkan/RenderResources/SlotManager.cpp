#include "SlotManager.h"
#include "VulkanDescriptorSetLayout.h"


SlotManager::SlotManager(VulkanLogicalDevice *pDev,std::vector<IVulkanRenderSlot*> resources)
{
	_slots = resources;
	_pDev = pDev;

	_pLayout = new VulkanDescriptorSetLayout(pDev, _slots);
	
}


SlotManager::~SlotManager()
{
}
