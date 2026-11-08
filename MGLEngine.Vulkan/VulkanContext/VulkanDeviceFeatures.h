#pragma once
#include <vulkan/vulkan.hpp>

struct VulkanDeviceFeatures {
	VkPhysicalDeviceFeatures2 V1;
	VkPhysicalDeviceVulkan12Features V12;
	VkPhysicalDeviceVulkan13Features V13;
	VkPhysicalDeviceVulkan14Features V14;
	
	VulkanDeviceFeatures() {
		V1 = {};
		V12 = {};
		V13 = {};
		V14 = {};
		V1.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		V12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
		V13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
		V14.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
		V1.pNext = &V12;
		V12.pNext = &V13;
		V13.pNext = &V14;
		V14.pNext = nullptr;
	}
};