#pragma once
#include <vulkan/vulkan.hpp>
#include <vector>
#include <glm/glm.hpp>
class VulkanRenderingInfo {
	bool _bDepthBuffer=false;
	std::vector<VkRenderingAttachmentInfo> vAttachments;
	VkRenderingInfo _vkRenderingInfo;
public:
	VulkanRenderingInfo(glm::vec4 clearColor, VkImageView swapChainView,VkImage depth=VK_NULL_HANDLE)
	{
		_vkRenderingInfo
	}
	
};