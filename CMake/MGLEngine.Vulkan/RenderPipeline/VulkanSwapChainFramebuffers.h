#pragma once
#include "VulkanRenderPass.h"
#include "../VulkanContext/VulkanSwapChain.h"
#include <cassert>
#include "VulkanFramebuffer.h"

class VulkanSwapChainFramebuffers
{
	const VulkanSwapChain& _swapChain;
	const VulkanRenderPass& _renderPass;
	std::vector<VkFramebuffer> _framebuffers;
	const VulkanLogicalDevice& _logicalDevice;
public:
	VulkanSwapChainFramebuffers(const VulkanRenderPass& renderPass, const VulkanSwapChain& swapChain);
	~VulkanSwapChainFramebuffers();
	const VulkanSwapChain& GetSwapChain() const { return _swapChain; }
	VulkanFramebuffer GetFramebuffer(int i) const;
	size_t Size() const { return _framebuffers.size(); }
};

