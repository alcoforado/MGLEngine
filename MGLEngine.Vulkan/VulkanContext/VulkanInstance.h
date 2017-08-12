#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
#include "VulkanPhysicalDevice.h"
class VulkanInstance
{
	static int nErrors;
	static int nWarning;

	VkInstance _vkInstance;
	std::vector<VulkanLayerProperties> _vkLayers;
	std::vector<VulkanPhysicalDevice>  _vkPhysicalDevices;
	

	static  VkBool32 __stdcall DbgCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
		void *pUserData);
	std::vector<VulkanPhysicalDevice> ComputePhysicalDevices() const;
	std::vector<VulkanLayerProperties> ComputeAvailableLayers() const;

	

public:
	static bool HasErrors() { return nErrors != 0; }
	static bool HasWarnings() { return nWarning != 0; }

	const std::vector<VulkanLayerProperties>& GetAvailableLayers() const { return _vkLayers; }
	const std::vector<VulkanPhysicalDevice>& GetPhysicalDevices() const { return _vkPhysicalDevices; }
	VkInstance GetHandle() const { return _vkInstance; }
	VulkanInstance();
	~VulkanInstance();
};

