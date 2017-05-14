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
	void AddColorAttachementReference(std::string name, VkImageLayout layout);

	
	~VulkanSubPass();
};

