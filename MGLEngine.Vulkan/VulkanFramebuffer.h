#pragma once
#include "RenderPipeline/VulkanRenderPass.h"
#include "VulkanContext/VulkanSwapChain.h"

class VulkanFramebuffer
{
	const VulkanSwapChain& _swapChain;
	std::vector<VkFramebuffer> _framebuffers;
public:
	VulkanFramebuffer(const VulkanRenderPass& renderPass, const VulkanSwapChain& swapChain);
	~VulkanFramebuffer();
};

