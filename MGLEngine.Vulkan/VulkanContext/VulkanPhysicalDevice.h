#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
#include "VulkanLogicalDevice.h"
#include <glfw/glfw3.h>
#include "../VulkanMemoryProperties.h"

class VulkanInstance;

class VulkanPhysicalDevice {

	friend VulkanInstance;


	const VulkanInstance& _vulkanInstance;
	VkPhysicalDevice _handler;
	std::vector<VkQueueFamilyProperties> _queueFamilyProperties;
	VkPhysicalDeviceFeatures _features;
	VkPhysicalDeviceMemoryProperties _memoryProperties;
	std::vector<VulkanMemoryProperties> _memProperties;
	VkPhysicalDeviceProperties _graphicProperties;
	std::vector<VulkanLayerProperties> _layerProperties;

	VulkanPhysicalDevice(const VulkanInstance& inst,VkPhysicalDevice handler);
public:
	const VulkanInstance& GetVulkanInstance() const { return _vulkanInstance; }
	VkPhysicalDevice GetHandle() const  { return _handler; }
	std::vector<VkQueueFamilyProperties> GetFamilyProperties() const { return _queueFamilyProperties; }
	VulkanLogicalDevice CreateLogicalDevice(GLFWwindow *window) const;
	std::vector<VkQueueFamilyProperties> FindQueuesWithType(VkFlags flags) const;

	std::vector<VulkanMemoryProperties> GetMemoryProperties() const { return _memProperties; }
	uint32_t FindMemoryPropertyIndex(uint32_t allowedMemoryTypes, std::vector<enum VkMemoryPropertyFlagBits> flags) const;
	uint32_t FindQueueFamilyIndexWithType(VkFlags flags) const;

	uint32_t FindGraphicsQueueIndex() const { return FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);}

	std::vector<VulkanLayerProperties> GetAvailableLayerProperties();

};

