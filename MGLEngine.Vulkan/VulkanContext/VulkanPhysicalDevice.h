#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
#include "VulkanLogicalDevice.h"
#include <glfw/glfw3.h>

class VulkanInstance;

class VulkanPhysicalDevice {

	friend VulkanInstance;


	const VulkanInstance& _vulkanInstance;
	VkPhysicalDevice _handler;
	std::vector<VkQueueFamilyProperties> _queueFamilyProperties;
	VkPhysicalDeviceFeatures _features;
	VkPhysicalDeviceMemoryProperties _memoryProperties;
	VkPhysicalDeviceProperties _graphicProperties;
	std::vector<VulkanLayerProperties> _layerProperties;
	VulkanPhysicalDevice(const VulkanInstance& inst,VkPhysicalDevice handler);
public:
	const VulkanInstance& GetVulkanInstance() const { return _vulkanInstance; }
	VkPhysicalDevice GetHandler() const  { return _handler; };
	
	VulkanLogicalDevice CreateLogicalDevice(GLFWwindow *window) const;
	std::vector<VkQueueFamilyProperties> FindQueuesWithType(VkFlags flags) const;
	uint32_t FindQueueFamilyIndexWithType(VkFlags flags) const;
	std::vector<uint32_t> VulkanPhysicalDevice::FindQueueFamilyIndicesThatSupportPresentation(VkSurfaceKHR surface) const;

	std::vector<VulkanLayerProperties> GetAvailableLayerProperties();

};

