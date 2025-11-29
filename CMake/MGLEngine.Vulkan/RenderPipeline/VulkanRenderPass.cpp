#include "VulkanRenderPass.h"
#include <MGLEngine.Shared/Utils/Exception.h>
#include <algorithm>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../VulkanUtils.h"

VulkanRenderPass::VulkanRenderPass(const VulkanLogicalDevice* device)
	:_logicalDevice(*device)
{
	_isLoaded = false;
}


VulkanRenderPass::~VulkanRenderPass()
{
	if (_isLoaded)
	{
		vkDestroyRenderPass(_logicalDevice.GetHandle(), _renderPass, nullptr);
	}
}




VulkanSubPass& VulkanRenderPass::AddGraphicSubpass(std::string name)
{
	VulkanSubPass subpass(VK_PIPELINE_BIND_POINT_GRAPHICS);
	_subpasses.push_back(subpass);
	if (_subpassesNameMapping.find(name) != _subpassesNameMapping.end())
	{
		throw new Exception("Error Subpass name must be unique");
	}
	_subpassesNameMapping[name] = _subpasses.size() - 1;
	return _subpasses.back();
}

VulkanSubPass& VulkanRenderPass::GetSubpass(std::string name)
{
	if (_subpassesNameMapping.find(name) == _subpassesNameMapping.end())
	{
		throw new Exception("Error subpass with name %s not found",name.c_str());
	}
	return _subpasses[_subpassesNameMapping[name]];
}

VkRenderPass VulkanRenderPass::GetHandle() const
{
	if (!_isLoaded)
	{
		throw new Exception("Render Pass was not loaded yet. Call Load method before you can get a handle");
	}
	return _renderPass;
}


void VulkanRenderPass::AddColorDescription(std::string name, VkAttachmentDescription desc)
{
	if (_colorNameMapping .find(name) != _colorNameMapping.end())
	{
		throw new Exception("Color Description already added");
	}
	_colorAttachments.push_back(desc);
	_colorNameMapping[name] = _colorAttachments.size() - 1;
}


VkRenderPass VulkanRenderPass::Load()
{
	if (_isLoaded)
	{
		vkDestroyRenderPass(_logicalDevice.GetHandle(), _renderPass, nullptr);
	}

	//Create subpasses structures.
	std::vector<VkSubpassDescription> subpasses;
	std::vector<std::vector<VkAttachmentReference>> attachments;
	for(auto subpass: _subpasses)
	{
		VkSubpassDescription vkpass = {};
		vkpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		std::vector<VkAttachmentReference> v;
		for(VulkanAttachmentReference ref: subpass.GetColorAttachements())
		{
			VkAttachmentReference result;
			result.attachment = static_cast<uint32_t>(this->_colorNameMapping[ref.name]);
			result.layout = ref.layout;
			v.push_back(result);
		}
		attachments.push_back(v);
		vkpass.colorAttachmentCount = static_cast<uint32_t>(attachments.back().size());
		vkpass.pColorAttachments = attachments.back().data();
		subpasses.push_back(vkpass);
	}


	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(_colorAttachments.size());
	renderPassInfo.pAttachments = _colorAttachments.data();
	renderPassInfo.subpassCount = static_cast<uint32_t>(subpasses.size());
	renderPassInfo.pSubpasses = subpasses.data();
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;


	auto err=vkCreateRenderPass(_logicalDevice.GetHandle(), &renderPassInfo, nullptr, &_renderPass);
	AssertVulkanSuccess(err);
	_isLoaded = true;
	return _renderPass;
	

}
