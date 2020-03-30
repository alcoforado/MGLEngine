#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include<string>
struct VulkanLayerProperties {
	VkLayerProperties layer;
	std::vector<VkExtensionProperties> extensions;

	std::string getName() const
	{
		return std::string(layer.layerName);
	}
};

