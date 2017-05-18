#include "VulkanSwapChainFramebuffers.h"
#include "../VulkanContext/VulkanSwapChain.h"
#include <cassert>
#include "../VulkanUtils.h"


VulkanSwapChainFramebuffers::VulkanSwapChainFramebuffers(const VulkanRenderPass& renderPass,const VulkanSwapChain& swapChain)
	:_swapChain(swapChain)
{
	auto imageViews = swapChain.GetImageViews();
	assert(renderPass.GetColorAttachments().size() == 1);
	for (auto imageView : imageViews)
	{
		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass.GetHandle();
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = &imageView;
		framebufferInfo.width = swapChain.GetExtent().width;
		framebufferInfo.height = swapChain.GetExtent().height;
		framebufferInfo.layers = 1;
		
		VkFramebuffer vkFramebuffer;
		auto err = vkCreateFramebuffer(swapChain.GetLogicalDevice().GetHandle(), &framebufferInfo, nullptr, &vkFramebuffer);
		AssertVulkanSuccess(err);
		_framebuffers.push_back(vkFramebuffer);

	}
}

VulkanSwapChainFramebuffers::~VulkanSwapChainFramebuffers()
{
	for(auto framebuffer : _framebuffers)
	{
		vkDestroyFramebuffer(_swapChain.GetLogicalDevice().GetHandle(),framebuffer,nullptr);
	}
}
