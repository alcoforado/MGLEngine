#pragma once
#include <vulkan/vulkan.h>
#include "VulkanSurface.h"
#include "VulkanLogicalDevice.h"
#include "../RenderPipeline/VulkanSemaphore.h"

class VulkanSwapChain
{
	VulkanSurface  _surface;
	const VulkanLogicalDevice& _logicalDevice;
	VkSwapchainKHR _handle;
	VkFormat _imageFormat;  
	int _imageColorSpace; 
	VkExtent2D _dims;
	std::vector<VkImage> _images;
	std::vector<VkImageView> _imagesviews;
	uint32_t _nextImageIndex;
	
	
	public:
	VulkanSwapChain(GLFWwindow *window,VulkanLogicalDevice& device);
	const VulkanLogicalDevice& GetLogicalDevice()const { return _logicalDevice; }
	VkExtent2D GetExtent() const { return _dims; }
	~VulkanSwapChain();
	VkFormat GetImageFormat() const { return _imageFormat; }
	std::vector<VkImageView> GetImageViews() const { return _imagesviews; }
	void  NextImagePipelineAsync(VulkanSemaphore* sToSignal, VulkanFence *fenceToSignal);
	VkSwapchainKHR GetHandle() { return _handle; }
	void Present(const VulkanSemaphore* lock);
	uint32_t GetCurrentImageIndex() const { return _nextImageIndex; }
};

