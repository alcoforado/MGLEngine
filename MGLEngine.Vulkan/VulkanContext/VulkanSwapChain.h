#pragma once
#include <vulkan/vulkan.h>
#include "VulkanSurface.h"
#include "VulkanLogicalDevice.h"

class VulkanSwapChain
{
	const VulkanSurface&  _surface;
	const VulkanLogicalDevice& _logicalDevice;
	VkSwapchainKHR _handle;
	VkFormat _imageFormat;  
	int _imageColorSpace; 
	VkExtent2D _dims;
	std::vector<VkImage> _images;
	std::vector<VkImageView> _imagesviews;
	public:
	VulkanSwapChain(const VulkanSurface &surface,const  VulkanLogicalDevice &device);
	~VulkanSwapChain();
};

