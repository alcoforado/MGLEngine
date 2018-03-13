#include "VulkanDescriptorSetLayout.h"
#include "VulkanInputLayout.h"
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderResource.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include "VulkanPipeline.h"

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanLogicalDevice* device,
	std::vector<IVulkanRenderResource*>& v)
{
	_dev = device;
	std::vector<VkDescriptorSetLayoutBinding> vLayout;
	for (auto r: v)
	{
		vLayout.push_back(r->GetVulkanDescriptor());
	}
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = vLayout.size();
	layoutInfo.pBindings = &(vLayout[0]);


	VkResult result = vkCreateDescriptorSetLayout(_dev->GetHandle(), &layoutInfo, nullptr, &_handle);
	AssertVulkanSuccess(result);

}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
{
	vkDestroyDescriptorSetLayout(_dev->GetHandle(), _handle,nullptr);
}
