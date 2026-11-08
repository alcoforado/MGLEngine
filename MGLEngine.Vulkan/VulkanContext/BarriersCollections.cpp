#include "BarriersCollections.h"

BarrierCollection::BarrierCollection()
{
	
	CreateSwapChainImageReadyToPresentBarrier();
	CreateSwapChaingImageReadyToWriteBarrier();


	


}



void BarrierCollection::CreateSwapChainImageReadyToPresentBarrier()
{
	VkImageMemoryBarrier& barrier = SwapChainImageReadyToPresentBarrier;

	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; // No need to preserve information on the origianl buffer, so I don't care what is the original format 
	barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; //Ready to Write
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;  //No queue transfer here
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;  //No queue transfer here
	barrier.image = VK_NULL_HANDLE; // Your current swapchain image
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; //This image will be used to store pixels. (Some images can have more than one role when they are created). Not the case of this engine though
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	// Define where synchronization happens
	barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT; //flush all writes cached to the image, I will present it  
	barrier.dstAccessMask = 0; //Presentation is handed to the OS, OS has its own cache system outside Vulkan. 
}

void BarrierCollection::CreateSwapChaingImageReadyToWriteBarrier()
{
	//SwapChaingImageReadyToWriteBarrier
	VkImageMemoryBarrier& barrier = SwapChainImageReadyToWriteBarrier;

	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED; // No need to preserve information on the origianl buffer, so I don't care what is the original format 
	barrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; //Ready to Write
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;  //No queue transfer here
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;  //No queue transfer here
	barrier.image = VK_NULL_HANDLE; // Your current swapchain image
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; //This image will be used to store pixels. (Some images can have more than one role when they are created). Not the case of this engine though
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	// Define where synchronization happens
	barrier.srcAccessMask = 0;	//the src stage has no cache, so no bother.
	barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT; //Clean all write cache, because new rendering will start
}

void BarrierCollection::WriteTransitionToRendering(VulkanCommandBuffer& cmdBuffer, VkImage img)
{
	SwapChainImageReadyToWriteBarrier.image = img;

	cmdBuffer.ImageMemoryBarrier(
		SwapChainImageReadyToWriteBarrier,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
	
	SwapChainImageReadyToWriteBarrier.image = VK_NULL_HANDLE;
}

void BarrierCollection::WriteTransitionToPresentation(VulkanCommandBuffer& cmdBuffer, VkImage img)
{
	SwapChainImageReadyToPresentBarrier.image = img;

	cmdBuffer.ImageMemoryBarrier(
		SwapChainImageReadyToWriteBarrier,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

	SwapChainImageReadyToPresentBarrier.image = VK_NULL_HANDLE;
}
