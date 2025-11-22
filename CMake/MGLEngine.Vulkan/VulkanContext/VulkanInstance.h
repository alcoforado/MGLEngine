#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
#include "VulkanPhysicalDevice.h"
class VulkanInstance
{
	static const char* LUNAR_VALIDATION_LAYER;
	static const char* DEBUG_REPORT_EXTENSION;


	static int nErrors;
	static int nWarning;

	struct VulkanVersion
	{
		int Major;
		int Minor;
		int Version;
	};



	VkInstance _vkInstance;
	std::vector<MVulkanLayer> _vkLayers;
	std::vector<VulkanPhysicalDevice>  _vkPhysicalDevices;
	

	static  VkBool32 __stdcall DbgCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
		void *pUserData);
	VkDebugReportCallbackEXT _vk_debug_report_callback_ext; //To contain the vulkan handle for the debug callback


	std::vector<VulkanPhysicalDevice> ComputePhysicalDevices() const;
	std::vector<MVulkanLayer> ComputeAvailableLayers() const;

	

public:
	static bool HasErrors() { return nErrors != 0; }
	static bool HasWarnings() { return nWarning != 0; }
	bool HasLayer(std::string layerName) const;
	VulkanVersion GetVulkanVersion() const;
	const std::vector<MVulkanLayer>& GetAvailableLayers() const { return _vkLayers; }
	const std::vector<VulkanPhysicalDevice>& GetPhysicalDevices() const { return _vkPhysicalDevices; }
	VkInstance GetHandle() const { return _vkInstance; }
	VulkanInstance();
	VulkanInstance(std::string appName, bool enableDebug);

	~VulkanInstance();
};

