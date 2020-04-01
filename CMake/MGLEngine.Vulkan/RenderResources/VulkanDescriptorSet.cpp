#include "VulkanDescriptorSet.h"
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include  <MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetPool.h>

void VulkanDescriptorSet::InitializeDescriptorSet(VkDescriptorSet dsHandle)
{
	_dsHandle = dsHandle;

	//Allocate the bindings
	for(IVulkanRenderSlot *s : _pLayout->GetSlots())
	{
		auto bind = s->Bind(this);
		_bindings.push_back(bind);

	}
}

VulkanDescriptorSet::VulkanDescriptorSet(VulkanDescriptorSetLayout* pLayout)
{
	_pLayout = pLayout;
	_pLayout->GetVulkanLogicalDevice()->GetDescriptorSetPool()->RegisterDescriptorSet(this);
}

VulkanDescriptorSet::~VulkanDescriptorSet()
{
	
}

 IVulkanSlotBinding* VulkanDescriptorSet::GetBinding(IVulkanRenderSlot* pSlot)
{
	int index = 0;
	for (IVulkanRenderSlot* s : _pLayout->GetSlots())
	{
		if (s == pSlot)
			return _bindings[index];
		index++;
	}
	throw std::exception("Bind not found");
}

void VulkanDescriptorSet::LoadIfNeeded()
{
	for (auto b : _bindings)
	{
		if (b->NeedUpdate())
			b->Update();
	}
}
