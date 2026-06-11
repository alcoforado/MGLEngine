#pragma once
#include <vulkan/vulkan.h>
#include "VulkanSurface.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChainOptions.h"
class VulkanSwapChain
{
	public:
		struct NextImage {
			uint32_t index;
			uint32_t bNeedResize;
		};

	public:
		const VulkanSurface&  _surface;
		VulkanSwapChainOptions _options;
		VulkanLogicalDevice& _logicalDevice;
		VkSwapchainKHR _swapChainHandle;
		VkFormat _imageFormat;  
		VkColorSpaceKHR _imageColorSpace; 
		VkExtent2D _dims;
		std::vector<VkImage> _images;
		std::vector<VkImageView> _imagesviews;
		uint32_t _currentImageIndex;
	private:
		void CreateSwapChain();
		void CreateImageViews();
		
	public:
		VulkanSwapChain(const VulkanSurface &surface, VulkanLogicalDevice& device, VulkanSwapChainOptions options);
		const VulkanLogicalDevice* GetLogicalDevice()const { return &_logicalDevice; }
		~VulkanSwapChain();
		size_t NImages() const { return _images.size(); }	
		VkExtent2D GetExtent2D() const { return _dims; }
		VkFormat GetImageFormat() const { return _imageFormat; }
		std::vector<VkImageView> GetImageViews() const { return _imagesviews; }
		NextImage  NextImagePipelineAsync(VulkanSemaphore* sToSignal=nullptr, VulkanFence *fenceToSignal=nullptr);
		VkSwapchainKHR GetHandle() { return _swapChainHandle; }
		void Present(const VulkanSemaphore* lock);
		uint32_t GetCurrentImageIndex() const { return _currentImageIndex; }
};


