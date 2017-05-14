#include "VulkanSubPass.h"






VulkanSubPass::VulkanSubPass(VkPipelineBindPoint bindPoint)
{
	Subpass = {};
	Subpass.pipelineBindPoint = bindPoint;
}


void VulkanSubPass::AddColorAttachementReference(std::string name, VkImageLayout layout)
{
	VulkanAttachmentReference ref;
	ref.attachment = -1;
	ref.name = name;
	ref.layout = layout;
	ColorAttachments.push_back(ref);

}



VulkanSubPass::~VulkanSubPass()
{
}
