#pragma once
#include <vulkan/vulkan.hpp>
#include "VulkanCommandBuffer.h"
class BarrierCollection {
	VulkanImageMemoryBarrier SwapChainImageReadyToWriteBarrier;
	VulkanImageMemoryBarrier SwapChainImageReadyToPresentBarrier;
	VulkanImageMemoryBarrier DepthBufferTransitionToRendering = {};
private:
	void InitRenderingTransition();
	void InitPresentationTransition();
public:
	BarrierCollection();

	const VulkanImageMemoryBarrier& ColorTransitionToRendering(VkImage img);
	const VulkanImageMemoryBarrier& ColorTransitionToPresentation(VkImage img);

	const VulkanImageMemoryBarrier& DepthTransitionToRendering(VkImage img);


};