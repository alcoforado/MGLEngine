#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
#include "VulkanPhysicalDevice.h"
class VulkanInstance
{
	VkInstance _vkInstance;
	std::vector<VulkanLayerProperties> _vkLayers;
	std::vector<VulkanPhysicalDevice>  _vkPhysicalDevices;
	


	std::vector<VulkanPhysicalDevice> ComputePhysicalDevices() const;
	std::vector<VulkanLayerProperties> ComputeAvailableLayers() const;

	

public:
	const std::vector<VulkanLayerProperties>& GetAvailableLayers() const { return _vkLayers; }
	const std::vector<VulkanPhysicalDevice>& GetPhysicalDevices() const { return _vkPhysicalDevices; }
	VkInstance GetHandle() const { return _vkInstance; }
	VulkanInstance();
	~VulkanInstance();
};

