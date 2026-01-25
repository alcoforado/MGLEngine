#include "VulkanSwapChain.h"
#include "../VulkanUtils.h"
#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanPhysicalDevice.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanFence.h>

VulkanSwapChain::VulkanSwapChain(const VulkanSurface& surface, const VulkanLogicalDevice& device, VulkanSwapChainOptions options)
	:_logicalDevice(device),
	_surface(surface)
{
	_options = options;
	CreateSwapChain();
	CreateImageViews();

	

}



void VulkanSwapChain::CreateSwapChain()
{
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = _surface.GetHandle();
	createInfo.minImageCount = _options.NBuffers;
	createInfo.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
	createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	createInfo.imageExtent = _surface.GetExtent2D();
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = 0; // Optional
	createInfo.pQueueFamilyIndices = nullptr; // Optional

	createInfo.preTransform = _logicalDevice.GetPhysicalDevice().GetCapabilitiesForSurface(_surface).currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	if (_options.VSync)
	{
		createInfo.presentMode = _logicalDevice.GetPhysicalDevice().IsPresentModeAvailableForSurface(_surface, VK_PRESENT_MODE_MAILBOX_KHR) ? VK_PRESENT_MODE_MAILBOX_KHR : VK_PRESENT_MODE_FIFO_KHR;
	}
	else
	{
		createInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

	}
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	_imageFormat = createInfo.imageFormat;
	_imageColorSpace = createInfo.imageColorSpace;
	_dims = createInfo.imageExtent;

	auto err = vkCreateSwapchainKHR(_logicalDevice.GetHandle(), &createInfo, nullptr, &_swapChainHandle);
	AssertVulkanSuccess(err);

	//Implementation moved to constructor
}


void VulkanSwapChain::CreateImageViews()
{
	//Get The imageds handlers

	uint32_t imagesCount;
	vkGetSwapchainImagesKHR(_logicalDevice.GetHandle(), _swapChainHandle, &imagesCount, nullptr);
	_images.resize(imagesCount);
	vkGetSwapchainImagesKHR(_logicalDevice.GetHandle(), _swapChainHandle, &imagesCount, _images.data());


	//Get images view;
	for (auto img : _images)
	{

		VkImageViewCreateInfo createViewInfo = {};
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
		auto err = vkCreateImageView(_logicalDevice.GetHandle(), &createViewInfo, nullptr, &view);
		AssertVulkanSuccess(err);

		_imagesviews.push_back(view);
	}
}


VulkanSwapChain::~VulkanSwapChain()
{
	for (auto img : _imagesviews)
		vkDestroyImageView(_logicalDevice.GetHandle(), img, nullptr);
	vkDestroySwapchainKHR(_logicalDevice.GetHandle(), _swapChainHandle, nullptr);
}

uint32_t  VulkanSwapChain::NextImagePipelineAsync(VulkanSemaphore* sToSignal, VulkanFence* fenceToSignal)
{
	vkAcquireNextImageKHR(_logicalDevice.GetHandle(),
		_swapChainHandle,
		std::numeric_limits<uint64_t>::max(),
		sToSignal == nullptr ? VK_NULL_HANDLE : sToSignal->GetHandle(),
		fenceToSignal == nullptr ? VK_NULL_HANDLE : fenceToSignal->GetHandle(),
		&_currentImageIndex);
	return _currentImageIndex;
}

void VulkanSwapChain::Present(const VulkanSemaphore* lock)
{
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	auto lh = lock->GetHandle();
	auto h = this->GetHandle();

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &lh;
	VkSwapchainKHR swapChains[] = { h };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &_currentImageIndex;
	presentInfo.pResults = nullptr;
	auto err = vkQueuePresentKHR(_logicalDevice.GetGraphicQueue()->GetHandle(), &presentInfo);
	AssertVulkanSuccess(err);

}
