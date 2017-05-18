#pragma once
#include "VulkanRenderPass.h"
#include "../VulkanContext/VulkanSwapChain.h"

class VulkanSwapChainFramebuffers
{
	const VulkanSwapChain& _swapChain;
	std::vector<VkFramebuffer> _framebuffers;
public:
	VulkanSwapChainFramebuffers(const VulkanRenderPass& renderPass, const VulkanSwapChain& swapChain);
	~VulkanSwapChainFramebuffers();
};

