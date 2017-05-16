#pragma once
#include <vulkan/vulkan.h>
#include <vector>


struct VulkanAttachmentReference : public VkAttachmentReference
{
	std::string name;
};

class VulkanSubPass
{
	VkSubpassDescription Subpass;
	std::vector<VulkanAttachmentReference> ColorAttachments;
public:
	
	
	VulkanSubPass(VkPipelineBindPoint bindPoint);
	VulkanSubPass& RefColorAttachement(std::string name, enum VkImageLayout layout);
	std::vector<VulkanAttachmentReference>& GetColorAttachements() { return ColorAttachments; }
	
	~VulkanSubPass();
};

