#pragma once
#include <vulkan/vulkan.hpp>
#include "VulkanCommandBuffer.h"
class BarrierCollection {
	VkImageMemoryBarrier SwapChainImageReadyToWriteBarrier;
	VkImageMemoryBarrier SwapChainImageReadyToPresentBarrier;

private:
	void CreateSwapChaingImageReadyToWriteBarrier();
	void CreateSwapChainImageReadyToPresentBarrier();
public:
	BarrierCollection();

	void WriteTransitionToRendering(VulkanCommandBuffer& cmdBuffer, VkImage img);
	void WriteTransitionToPresentation(VulkanCommandBuffer& cmdBuffer, VkImage img);

	

};