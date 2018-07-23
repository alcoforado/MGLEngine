#include "VulkanDescriptorSet.h"
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include  <MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h>


VulkanDescriptorSet::VulkanDescriptorSet(VulkanDescriptorSetLayout* pLayout)
{
	_pLayout = pLayout;
}

VulkanDescriptorSet::~VulkanDescriptorSet()
{
	
}
