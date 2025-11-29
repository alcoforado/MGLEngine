	#include "VulkanApp.h"
#include<algorithm>
#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>
using namespace MGL;
MGL::VulkanApp::~VulkanApp() {
	// Destructor implementation (if needed)
}


MGL::VulkanApp::VulkanApp() {
	//default values for options
	_windowOptions.Width = 800;
	_windowOptions.Height = 60;
	_windowOptions.FullScreen= false;
	_windowOptions.Title = "Vulkan Application";
	_pWindow = nullptr;
	_pVulkanInstance = nullptr;
}

void MGL::VulkanApp::Init() {
		_pWindow = new Window(_windowOptions);
		_pVulkanInstance = new VulkanInstance(
			_vulkanConfiguration.Name, 
			_vulkanConfiguration.EnableDebug);
		ChoosePhysicalDevice();
		CreateVulkanSurface();
		CreateQueues();
		
}

void MGL::VulkanApp::CreateVulkanSurface() {
	_pVulkanSurface = new VulkanSurface(_pVulkanInstance, _pWindow);
}

void MGL::VulkanApp::CreateQueues() {
	int32_t graphicQueueIndex = _pPhysicalDevice->FindQueueFamilyIndex([](auto family) {
		return family.IsGraphic && family.SupportPresentation;
	});
	if (graphicQueueIndex == -1) {
		throw new Exception("No suitable graphic queue found that supports presentation.");
	}
	_pLogicalDevice = new VulkanLogicalDevice(*_pPhysicalDevice, graphicQueueIndex);
	

}

void MGL::VulkanApp::CreateSwapChain() {
		VkSwapchainCreateInfoKHR createInfo = {};
		auto capabilities = _pLogicalDevice->GetPhysicalDevice().GetCapabilitiesForSurface(*_pVulkanSurface);
		uint32_t imageCount = _vulkanConfiguration.SwapChainSize;
		if (capabilities.minImageCount!=0)
			imageCount = imageCount < capabilities.minImageCount ? capabilities.minImageCount : imageCount;
		if (capabilities.maxImageCount != 0)
			imageCount = imageCount > capabilities.maxImageCount ? capabilities.maxImageCount : imageCount;
		

		//Create Swap Chain
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _pVulkanSurface->GetHandle();
		createInfo.minImageCount = _vulkanConfiguration.SwapChainSize;
		createInfo.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
		createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		createInfo.imageExtent = _pVulkanSurface->GetExtent2D();
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional

		createInfo.preTransform = capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		if (_vulkanConfiguration.VSync)
		{
			createInfo.presentMode = _pLogicalDevice->GetPhysicalDevice().IsPresentModeAvailableForSurface(*_pVulkanSurface, VK_PRESENT_MODE_MAILBOX_KHR) ? VK_PRESENT_MODE_MAILBOX_KHR : VK_PRESENT_MODE_FIFO_KHR;
		}
		else
		{
			createInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

		}
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		_swapChain.imageFormat = createInfo.imageFormat;
		_swapChain.imageColorSpace = createInfo.imageColorSpace;
		_swapChain.dims = createInfo.imageExtent;
		auto err = vkCreateSwapchainKHR(_pLogicalDevice->GetHandle(), &createInfo, nullptr, &(_swapChain.handle));
		AssertVulkanSuccess(err);

		//Implementation moved to constructor

}

void MGL::VulkanApp::CreateSwapChainImageViews() {
	//Get The imageds handlers

	uint32_t imagesCount;
	vkGetSwapchainImagesKHR(_pLogicalDevice->GetHandle(), _swapChain.handle, &imagesCount, nullptr);
	_swapChain.images.resize(imagesCount);
	vkGetSwapchainImagesKHR(_pLogicalDevice->GetHandle(), _swapChain.handle, &imagesCount, _swapChain.images.data());


	//Get images view;
	for (auto img : _swapChain.images)
	{

		VkImageViewCreateInfo createViewInfo = {};
		createViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createViewInfo.image = img;
		createViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createViewInfo.format = _swapChain.imageFormat;
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
		auto err = vkCreateImageView(_pLogicalDevice->GetHandle(), &createViewInfo, nullptr, &view);
		AssertVulkanSuccess(err);

		_swapChain.imagesviews.push_back(view);
	}

}

void MGL::VulkanApp::ChoosePhysicalDevice()
{
	auto &v=_pVulkanInstance->GetPhysicalDevices();
	std::vector<int> suitableDevices;
	for (int i = 0; i < v.size(); i++) {
		suitableDevices.push_back(i);

	}
	std::sort(suitableDevices.begin(),suitableDevices.end(),[v](int a, int b) {
		int scoreA = deviceScore(v[a]);
	    int scoreB=deviceScore(v[b]);
		if (scoreA == scoreB)
		{
			return v[a].GetProperties().limits.maxImageDimension1D > v[b].GetProperties().limits.maxImageDimension1D;
		}
		return scoreA > scoreB;
	});
	_pPhysicalDevice =  &(v[suitableDevices[0]]);
}

int deviceScore(const VulkanPhysicalDevice& device) {
	int score = 0;
	// Example criteria for scoring
	if (device.IsDiscrete()) {
		score += 5000; // Prefer discrete GPUs
	}
	if (device.IsIntegrated())
	{
		score += 4000;
	}
	if (device.IsCPU()) {
		score += 3000; // Least preferred
	}
	if (device.IsVirtual()) {
		score = +2000;
	}
	if (device.HasComputeQueue()) {
		score += 500;
	}
	
	
	return score;
}

