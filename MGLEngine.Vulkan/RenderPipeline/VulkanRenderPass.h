#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanSubPass.h"
#include <map>


class VulkanRenderPass
{
	std::map<std::string, size_t> _colorNameMapping;
	std::vector<VkAttachmentDescription> _colorAttachments;

	std::vector<VulkanSubPass> _subpasses;

	VkRenderPass _renderPass;
	bool _isLoaded;
public:
	VulkanRenderPass();
	~VulkanRenderPass();

	void AddColorDescription(std::string name, VkAttachmentDescription desc);
	std::vector<VkAttachmentDescription> GetColorAttachments() const{ return _colorAttachments; }
	void AddSubpass(VulkanSubPass subpass);

	void Load();
};

