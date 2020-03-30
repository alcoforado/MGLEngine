#pragma once
#include <vulkan/vulkan.h>
#include <vector>
class VulkanSwapChainFramebuffers;
class VulkanRenderPass;
class VulkanSwapChain;

class VulkanFramebuffer
{
	friend VulkanSwapChainFramebuffers;


	const VulkanSwapChain& _swapChain;
	const VulkanRenderPass& _renderPass;
	VkFramebuffer _framebuffer;
	VulkanFramebuffer(const VulkanRenderPass& renderPass, const VulkanSwapChain& swapChain, VkFramebuffer _framebuffer);
public:
	const VulkanSwapChain& GetSwapChain()const  { return _swapChain; }
	const VulkanRenderPass& GetRenderPass() const { return _renderPass; }
	VkFramebuffer GetHandle() const { return _framebuffer; }
	~VulkanFramebuffer();
};

