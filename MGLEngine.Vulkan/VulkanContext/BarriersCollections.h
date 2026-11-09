#pragma once
#include <vulkan/vulkan.hpp>
#include "VulkanCommandBuffer.h"
class BarrierCollection {
	VulkanImageMemoryBarrier SwapChainImageReadyToWriteBarrier;
	VulkanImageMemoryBarrier SwapChainImageReadyToPresentBarrier;

private:
	void InitRenderingTransition();
	void InitPresentationTransition();
public:
	BarrierCollection();

	

	const VulkanImageMemoryBarrier& TransitionToRendering(VkImage img);
	const VulkanImageMemoryBarrier& TransitionToPresentation(VkImage img);

};