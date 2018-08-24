#include "VulkanInstance.h"
#include "../vulkanutils.h"
#include  <Utils/Exception.h>
#include <glfw/glfw3.h>
#include <cassert>
#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

int VulkanInstance::nErrors = 0;
int VulkanInstance::nWarning = 0;


VkBool32 __stdcall VulkanInstance::DbgCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
	size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
	void *pUserData) {
	size_t size = strlen(pMsg);
	size += 100;
	char *message = (char *)malloc(size);

	assert(message);

	if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
		sprintf_s(message, size, "ERROR: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
		VulkanInstance::nErrors++;
	}
	else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
		sprintf_s(message, size, "WARNING: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
		VulkanInstance::nWarning++;
	}
	else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
		sprintf_s(message, size, "INFO: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
	}
	else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
		sprintf_s(message, size, "DEBUG: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
	}

	vulkanError << message << std::endl;
	free(message);

	/*
	* false indicates that layer should not bail-out of an
	* API call that had validation failures. This may mean that the
	* app dies inside the driver due to invalid parameter(s).
	* That's what would happen without validation layers, so we'll
	* keep that behavior here.
	*/
	return false;
}



VulkanInstance::VulkanInstance()
{
	_vkLayers = this->ComputeAvailableLayers();
	//Get GLFW Necessary Vulkan extensions and layers
	std::vector<const char*> vulkan_extensions;
	std::vector<const char*> device_extensions;
	std::vector<const char*> vulkan_layers;

	uint32_t count;
	const char** extensions = glfwGetRequiredInstanceExtensions(&count);
	for (uint32_t i = 0; i < count; i++)
	{
		vulkan_extensions.push_back(extensions[i]);
	}

	//If Debug mode, add validation layers and set report function
#ifdef _DEBUG
	vulkan_layers.push_back("VK_LAYER_LUNARG_standard_validation");
	vulkan_extensions.push_back("VK_EXT_debug_report");
#endif


	//Set Application Info
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = NULL;
	app_info.pApplicationName = "MGLEngine";
	app_info.applicationVersion = 1;
	app_info.pEngineName = "MGLEngine";
	app_info.engineVersion = 1;
	app_info.apiVersion = VK_API_VERSION_1_1;


	//Set Instance Info
	VkInstanceCreateInfo inst_info = {};
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = (uint32_t)vulkan_layers.size();
	inst_info.ppEnabledLayerNames = vulkan_layers.data();
	inst_info.enabledExtensionCount = (uint32_t)vulkan_extensions.size();
	inst_info.ppEnabledExtensionNames = vulkan_extensions.data();

#ifdef _DEBUG
	VkDebugReportCallbackCreateInfoEXT dbg_info;
	memset(&dbg_info, 0, sizeof(dbg_info));
	dbg_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	dbg_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
	dbg_info.pfnCallback = DbgCallback;
	inst_info.pNext = &dbg_info;
#endif
	VkResult err;
	err = vkCreateInstance(&inst_info, NULL, &(this->_vkInstance));
	if (err == VK_ERROR_INCOMPATIBLE_DRIVER) {
		throw new Exception("Cannot create Vulkan instance.\n");
	}
	else if (err) {
		throw new Exception("Vulkan initialization failed with error %s", MapVkResultToString(err).c_str());;
	}

	_vkPhysicalDevices = ComputePhysicalDevices();

	

}


VulkanInstance::~VulkanInstance()
{
}

std::vector<VulkanPhysicalDevice> VulkanInstance::ComputePhysicalDevices() const
{
	VkInstance inst = _vkInstance;

	std::vector<VulkanPhysicalDevice> result;
	uint32_t gpu_count = 1;
	VkResult res = vkEnumeratePhysicalDevices(inst, &gpu_count, NULL);
	assert(gpu_count);
	std::vector<VkPhysicalDevice> devs;
	devs.resize(gpu_count);

	res = vkEnumeratePhysicalDevices(inst, &gpu_count, devs.data());
	AssertVulkanSuccess(res);

	for (int i = 0; i<devs.size(); i++)
	{
		VulkanPhysicalDevice elem(*this,devs[i]);
		result.push_back(elem);
	}

	return result;
}




std::vector<VulkanLayerProperties> VulkanInstance::ComputeAvailableLayers() const
{
	/*
	* It's possible, though very rare, that the number of
	* instance layers could change. For example, installing something
	* could include new layers that the loader would pick up
	* between the initial query for the count and the
	* request for VkLayerProperties. The loader indicates that
	* by returning a VK_INCOMPLETE status and will update the
	* the count parameter.
	* The count parameter will be updated with the number of
	* entries loaded into the data pointer - in case the number
	* of layers went down or is smaller than the size given.
	*/
	VkLayerProperties *vk_props = NULL;
	VkResult res;
	uint32_t instance_layer_count = 0;
	do {
		res = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
		AssertVulkanSuccess(res);

		if (instance_layer_count == 0) {
			return std::vector<VulkanLayerProperties>();
		}

		vk_props = (VkLayerProperties *)realloc(vk_props, instance_layer_count * sizeof(VkLayerProperties));

		res = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props);
	} while (res == VK_INCOMPLETE);

	/*
	* Now gather the extension list for each instance layer.
	*/
	std::vector<VulkanLayerProperties> result;

	for (uint32_t i = 0; i < instance_layer_count; i++) {
		VulkanLayerProperties elem;
		elem.layer = vk_props[i];


		do {
			uint32_t instance_extension_count;
			res = vkEnumerateInstanceExtensionProperties(elem.layer.layerName, &instance_extension_count, NULL);
			AssertVulkanSuccess(res);

			if (instance_extension_count != 0) {
				elem.extensions.resize(instance_extension_count);
				VkExtensionProperties *instance_extensions = elem.extensions.data();
				res = vkEnumerateInstanceExtensionProperties(elem.layer.layerName, &instance_extension_count, instance_extensions);
			}
			result.push_back(elem);
		} while (res == VK_INCOMPLETE);
	}
	free(vk_props);
	return result;
}
