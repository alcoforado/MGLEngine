#pragma once
#include <vulkan/vulkan.h>
#include "VulkanSurface.h"
#include "VulkanLogicalDevice.h"

class VulkanSwapChain
{
	const VulkanSurface&  _surface;
	const VulkanLogicalDevice& _logicalDevice;
	VkSwapchainKHR _handle;
	int _imageFormat;  
	int _imageColorSpace; 

	std::vector<VkImage> _images; 
	public:
	VulkanSwapChain(const VulkanSurface &surface,const  VulkanLogicalDevice &device);
	~VulkanSwapChain();
};

