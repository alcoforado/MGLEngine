#include "VulkanSwapChainFramebuffers.h"
#include "../VulkanContext/VulkanSwapChain.h"
#include <cassert>
#include "../VulkanUtils.h"


VulkanSwapChainFramebuffers::VulkanSwapChainFramebuffers(const VulkanRenderPass& renderPass,const VulkanSwapChain& swapChain)
	:_swapChain(swapChain),_renderPass(renderPass),_logicalDevice(swapChain.GetLogicalDevice())
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
		vkDestroyFramebuffer(_logicalDevice.GetHandle(),framebuffer,nullptr);
	}
}

VulkanFramebuffer VulkanSwapChainFramebuffers::GetFramebuffer(int i) const
{
	assert(_framebuffers.size() > i);  
	return VulkanFramebuffer(_renderPass, _swapChain, _framebuffers[i]); 
}
