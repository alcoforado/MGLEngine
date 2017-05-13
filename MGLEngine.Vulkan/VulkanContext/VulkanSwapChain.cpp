#include "VulkanSwapChain.h"
#include "../VulkanUtils.h"


VulkanSwapChain::VulkanSwapChain(const VulkanSurface& surface, const VulkanLogicalDevice& device)
:_surface(surface),_logicalDevice(device)
{
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = _surface.GetHandle();
	createInfo.minImageCount = 3;
	createInfo.imageFormat = VK_FORMAT_A8B8G8R8_UNORM_PACK32;
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
	createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	
	
	auto err=vkCreateSwapchainKHR(device.GetHandle(), &createInfo, nullptr, &_handle);
	AssertVulkanSuccess(err);

	_imageFormat = createInfo.imageFormat;
	_imageColorSpace = createInfo.imageColorSpace;

	uint32_t imagesCount;
	vkGetSwapchainImagesKHR(_logicalDevice.GetHandle(), _handle, &imagesCount, nullptr);
	_images.resize(imagesCount);
	vkGetSwapchainImagesKHR(_logicalDevice.GetHandle(), _handle, &imagesCount, _images.data());







}

VulkanSwapChain::~VulkanSwapChain()
{
}
