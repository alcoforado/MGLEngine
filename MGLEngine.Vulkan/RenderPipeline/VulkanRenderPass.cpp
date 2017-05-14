#include "VulkanRenderPass.h"
#include "Utils/Exception.h"


VulkanRenderPass::VulkanRenderPass()
{
	_isLoaded = false;
}


VulkanRenderPass::~VulkanRenderPass()
{
}


void VulkanRenderPass::AddSubpass(VulkanSubPass subpass)
{
	_subpasses.push_back(subpass);
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


void VulkanRenderPass::Load()
{
	dsdfsg
}
