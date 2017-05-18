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
	const VulkanLogicalDevice& GetLogicalDevice()const { return _logicalDevice; }
	VkExtent2D GetExtent() const { return _dims; }
	~VulkanSwapChain();
	VkFormat GetImageFormat() const { return _imageFormat; }
	std::vector<VkImageView> GetImageViews() const { return _imagesviews; }
};

