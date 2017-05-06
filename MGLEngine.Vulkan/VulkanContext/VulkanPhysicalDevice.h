#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
struct VulkanPhysicalDevice {
	VkPhysicalDevice Handler;
	std::vector<VkQueueFamilyProperties> QueueFamilyProperties;
	VkPhysicalDeviceFeatures Features;
	VkPhysicalDeviceMemoryProperties MemoryProperties;
	VkPhysicalDeviceProperties GraphicProperties;
	std::vector<VulkanLayerProperties> LayerProperties;

	std::vector<VkQueueFamilyProperties> FindQueuesWithType(VkFlags flags)
	{
		std::vector<VkQueueFamilyProperties> result;
		for (int i = 0; i < QueueFamilyProperties.size(); i++)
		{
			if (QueueFamilyProperties[i].queueFlags & flags)
			{
				result.push_back(QueueFamilyProperties[i]);
			}
		}
		return result;
	}

	uint32_t FindQueueFamilyIndexWithType(VkFlags flags) const
	{
		for (int i = 0; i < QueueFamilyProperties.size(); i++)
		{
			if (QueueFamilyProperties[i].queueFlags & flags)
			{
				return i;
			}
		}
		return -1;
	}

};

