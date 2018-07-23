#include "VulkanDescriptorSet.h"
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include  <MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h>


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
}

VulkanDescriptorSet::~VulkanDescriptorSet()
{
	
}
