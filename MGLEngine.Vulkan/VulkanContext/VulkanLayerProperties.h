#pragma once

#include <vulkan/vulkan.h>
#include <vector>
struct VulkanLayerProperties {
	VkLayerProperties layer;
	std::vector<VkExtensionProperties> extensions;
};

