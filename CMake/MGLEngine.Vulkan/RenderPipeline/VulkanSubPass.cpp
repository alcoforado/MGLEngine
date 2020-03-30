#include "VulkanSubPass.h"






VulkanSubPass::VulkanSubPass(VkPipelineBindPoint bindPoint)
{
	Subpass = {};
	Subpass.pipelineBindPoint = bindPoint;
}


VulkanSubPass& VulkanSubPass::RefColorAttachement(std::string name, enum VkImageLayout layout)
{
	VulkanAttachmentReference ref;
	ref.attachment = -1;
	ref.name = name;
	ref.layout = layout;
	ColorAttachments.push_back(ref);
	return *this;

}



VulkanSubPass::~VulkanSubPass()
{
}
