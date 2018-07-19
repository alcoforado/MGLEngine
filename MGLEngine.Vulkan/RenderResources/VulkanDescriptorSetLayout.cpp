#include "VulkanDescriptorSetLayout.h"
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include  <MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h>

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanLogicalDevice* device,
	const std::vector<IVulkanRenderSlot*>& v)
{
	_dev = device;
	_resources = v;
	std::vector<VkDescriptorSetLayoutBinding> vLayout;
	for (auto r : v)
	{
		vLayout.push_back(r->GetVulkanDescriptor());
	}
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(vLayout.size());
	layoutInfo.pBindings = &(vLayout[0]);


	VkResult result = vkCreateDescriptorSetLayout(_dev->GetHandle(), &layoutInfo, nullptr, &_handle);
	AssertVulkanSuccess(result);

}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
{
	vkDestroyDescriptorSetLayout(_dev->GetHandle(), _handle, nullptr);
}


