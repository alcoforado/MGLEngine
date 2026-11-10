#include "BarriersCollections.h"

BarrierCollection::BarrierCollection()
{
	
	InitRenderingTransition();
	InitPresentationTransition();


	


}

void BarrierCollection::InitRenderingTransition()
{
	//SwapChaingImageReadyToWriteBarrier
	VkImageMemoryBarrier& barrier = SwapChainImageReadyToWriteBarrier.barrier;
	barrier = {};
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

	SwapChainImageReadyToWriteBarrier.srcPipeline = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	SwapChainImageReadyToWriteBarrier.dstPipeline = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
}


void BarrierCollection::InitPresentationTransition()
{
	VkImageMemoryBarrier& barrier = SwapChainImageReadyToPresentBarrier.barrier;
	barrier = {};
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

	SwapChainImageReadyToPresentBarrier.srcPipeline = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	SwapChainImageReadyToPresentBarrier.dstPipeline = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

}


const VulkanImageMemoryBarrier& BarrierCollection::DepthTransitionToRendering(VkImage img)
{
	if (DepthBufferTransitionToRendering.barrier.sType == 0)
	{
		VkImageMemoryBarrier& barrier = DepthBufferTransitionToRendering.barrier;
		barrier = {};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED; // No need to preserve information on the origianl buffer, so I don't care what is the original format 
		barrier.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL; //Optimal Depth Buffer
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;  //No queue transfer here
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;  //No queue transfer here
		barrier.image = img; // Your current swapchain image
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT; //This image will be used as a depth buffer
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		// Define where synchronization happens

		DepthBufferTransitionToRendering.srcPipeline = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		barrier.srcAccessMask = 0; //top of pipeline has no cache to concern about  
		
		DepthBufferTransitionToRendering.dstPipeline = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT; //By the time the depth test write starts all cache (write and read) should be flushed  
	}
	else
	{
		DepthBufferTransitionToRendering.barrier.image = img;
	}
	return DepthBufferTransitionToRendering;
}


const VulkanImageMemoryBarrier& BarrierCollection::ColorTransitionToRendering(VkImage img)
{
	SwapChainImageReadyToWriteBarrier.barrier.image = img;
	return SwapChainImageReadyToWriteBarrier;
}

const VulkanImageMemoryBarrier& BarrierCollection::ColorTransitionToPresentation(VkImage img)
{
	SwapChainImageReadyToPresentBarrier.barrier.image = img;
	return SwapChainImageReadyToPresentBarrier;
}

