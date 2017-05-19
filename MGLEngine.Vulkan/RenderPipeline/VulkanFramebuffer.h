#pragma once
#include <vulkan/vulkan.h>
#include <vector>
class VulkanRenderPass;
class VulkanSwapChain;

class VulkanFramebuffer
{
	const VulkanSwapChain& _swapChain;
	const VulkanRenderPass& _renderPass;
	VkFramebuffer _framebuffer;
public:
	VulkanFramebuffer(const VulkanRenderPass& renderPass, const VulkanSwapChain& swapChain, VkFramebuffer _framebuffer);
	const VulkanSwapChain& GetSwapChain()const  { return _swapChain; }
	const VulkanRenderPass& GetRenderPass() const { return _renderPass; }
	VkFramebuffer GetHandle() const { return _framebuffer; }
	~VulkanFramebuffer();
};

