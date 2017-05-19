#include "VulkanFramebuffer.h"



VulkanFramebuffer::VulkanFramebuffer(const VulkanRenderPass& renderPass, const VulkanSwapChain& swapChain, VkFramebuffer framebuffer)
	:_renderPass(renderPass),_swapChain(swapChain),_framebuffer(framebuffer)
{

}


VulkanFramebuffer::~VulkanFramebuffer()
{
}
