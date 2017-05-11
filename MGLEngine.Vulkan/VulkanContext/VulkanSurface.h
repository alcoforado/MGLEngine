#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <glfw/glfw3.h>

class VulkanPhysicalDevice;

struct PresentationGraphicsFamilyIndices
{
	uint32_t GraphicQueueFamily;
	uint32_t PresentationQueueFamily;
};

class VulkanSurface
{
	const VulkanPhysicalDevice& _physicalDevice;
	VkSurfaceKHR _vkSurface;
	VkSurfaceCapabilitiesKHR _capabilities;
	std::vector<VkSurfaceFormatKHR> _formats;
	std::vector<VkPresentModeKHR> _presentModes;
	uint32_t _windowWidth;
	uint32_t _windowHeight;
	
public:
	VulkanSurface(const VulkanPhysicalDevice& device,GLFWwindow* window);
	~VulkanSurface();
	VkSurfaceKHR GetHandle()const { return _vkSurface; }
	bool SupportsFormat(VkFormat format, VkColorSpaceKHR colorSpace)const;
	bool SupportsPresentation(VkPresentModeKHR present) const;
	bool SupportsImageCount(uint32_t i) const;
	VkExtent2D GetExtent() const;
	std::vector<uint32_t> FindQueueFamilyIndicesThatSupportPresentation() const;
	PresentationGraphicsFamilyIndices GetPresentationAndGraphicsQueusFamilyIndices() const;
	void CreateSwapChain();
	VkSurfaceCapabilitiesKHR GetCapabilities() const { return _capabilities; }
};

