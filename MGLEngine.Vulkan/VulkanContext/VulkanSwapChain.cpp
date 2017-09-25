#include "VulkanSwapChain.h"
#include "../VulkanUtils.h"
#include <vulkan/vulkan.h>


VulkanSwapChain::VulkanSwapChain(GLFWwindow *window,VulkanLogicalDevice& device)
:_logicalDevice(device),
_nextImageSemaphore(device),
_surface(device.GetPhysicalDevice(),window)
{
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = _surface.GetHandle();
	createInfo.minImageCount = 3;
	createInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
	createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	createInfo.imageExtent = _surface.GetExtent();
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;


	auto pgQueues = _surface.GetPresentationAndGraphicsQueusFamilyIndices();
	std::vector<uint32_t> queues;
	if (pgQueues.GraphicQueueFamily == pgQueues.PresentationQueueFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	else
	{
		queues.push_back(pgQueues.GraphicQueueFamily);
		queues.push_back(pgQueues.PresentationQueueFamily);
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queues.data();
	}
	createInfo.preTransform = _surface.GetCapabilities().currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = _surface.SupportsPresentation(VK_PRESENT_MODE_MAILBOX_KHR) ? VK_PRESENT_MODE_MAILBOX_KHR : VK_PRESENT_MODE_FIFO_KHR;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	
	
	auto err=vkCreateSwapchainKHR(device.GetHandle(), &createInfo, nullptr, &_handle);
	AssertVulkanSuccess(err);


	//Get The imageds handlers
	_imageFormat = createInfo.imageFormat;
	_imageColorSpace = createInfo.imageColorSpace;
	_dims = createInfo.imageExtent;
	uint32_t imagesCount;
	vkGetSwapchainImagesKHR(_logicalDevice.GetHandle(), _handle, &imagesCount, nullptr);
	_images.resize(imagesCount);
	vkGetSwapchainImagesKHR(_logicalDevice.GetHandle(), _handle, &imagesCount, _images.data());


	//Get images view;
	for(auto img : _images)
	{
	
		VkImageViewCreateInfo createViewInfo={};
		createViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createViewInfo.image = img;
		createViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createViewInfo.format = _imageFormat;
		createViewInfo.flags = 0;
		createViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		
		//no layers or mipmaps
		createViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createViewInfo.subresourceRange.baseMipLevel = 0;
		createViewInfo.subresourceRange.levelCount = 1;
		createViewInfo.subresourceRange.baseArrayLayer = 0;
		createViewInfo.subresourceRange.layerCount = 1;
	
		VkImageView view;
		err=vkCreateImageView(device.GetHandle(), &createViewInfo, nullptr, &view);
		AssertVulkanSuccess(err);

		_imagesviews.push_back(view);
	
	}

	
	
	

}

VulkanSwapChain::~VulkanSwapChain()
{
	for (auto img : _imagesviews)
		vkDestroyImageView(_logicalDevice.GetHandle(), img, nullptr);
	vkDestroySwapchainKHR(_logicalDevice.GetHandle(),_handle,nullptr);
}

VulkanSemaphore* VulkanSwapChain::NextImagePipelineAsync()
{
	vkAcquireNextImageKHR(_logicalDevice.GetHandle(), _handle, std::numeric_limits<uint64_t>::max(), _nextImageSemaphore.GetHandle(), VK_NULL_HANDLE, &_nextImageIndex);
	return &_nextImageSemaphore;
}

void VulkanSwapChain::Present(const VulkanSemaphore& lock)
{
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	auto lh = lock.GetHandle();
	auto h = this->GetHandle();

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &lh;
	VkSwapchainKHR swapChains[] = {h};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &_nextImageIndex;
	presentInfo.pResults = nullptr;
	auto err=vkQueuePresentKHR(_logicalDevice.GetGraphicQueue().GetHandle(),&presentInfo);
	AssertVulkanSuccess(err);

}
