#include "VulkanContext.h"
#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>
#include <Utils/Exception.h>
#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <fstream>

#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

static  VkBool32 __stdcall DbgCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
	size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
	void *pUserData) {
	size_t size = strlen(pMsg);
	size += 100;
	char *message = (char *)malloc(size);

	assert(message);

	if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
		sprintf_s(message, size, "ERROR: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
	}
	else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
		sprintf_s(message, size, "WARNING: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
	}
	else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
		sprintf_s(message, size, "INFO: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
	}
	else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
		sprintf_s(message, size, "DEBUG: [%s] Code %d : %s", pLayerPrefix, msgCode, pMsg);
	}

	(*VulkanContext::err) << message << std::endl;
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




std::ofstream* VulkanContext::err = new std::ofstream("vulkan_log.txt", std::ofstream::trunc);

VulkanContext::VulkanContext()
{

}


VulkanContext::~VulkanContext()
{
}





void VulkanContext::Initialize(GLFWwindow * window)
{
	//Get all layer properties and extensions
	_vkLayers = GetInstanceLayerProperties();




	std::ofstream out("log.txt",std::ofstream::trunc);
	for (int i = 0; i < _vkLayers.size(); i++)
	{
		out << _vkLayers[i].layer.layerName << " Desc: " << _vkLayers[i].layer.description << std::endl;
	}
	out.close();


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
	device_extensions = vulkan_extensions;
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
	app_info.apiVersion = VK_API_VERSION_1_0;

	
	//Set Instance Info
	VkInstanceCreateInfo inst_info = {};
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = (uint32_t) vulkan_layers.size();
	inst_info.ppEnabledLayerNames = vulkan_layers.data();
	inst_info.enabledExtensionCount = (uint32_t) vulkan_extensions.size();
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

	_vkDevices=GetPhysicalDevices(_vkInstance);

	//Create Device with the Queues
	assert(_vkDevices.size() > 0);
	float queue_priorities[1] = { 0.0 };
	VkDeviceQueueCreateInfo queue_info;
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.queueCount = 1;
	queue_info.pQueuePriorities = queue_priorities;
	queue_info.queueFamilyIndex = _vkDevices[0].FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);

	VkDeviceCreateInfo device_info = {};
	device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_info.pNext = NULL;
	device_info.queueCreateInfoCount = 1;
	device_info.pQueueCreateInfos = &queue_info;
	device_info.enabledExtensionCount = (uint32_t) device_extensions.size();
	device_info.ppEnabledExtensionNames = device_extensions.data();
	device_info.enabledLayerCount = 0;
	device_info.ppEnabledLayerNames = NULL;
	device_info.pEnabledFeatures = NULL;


	
	err = vkCreateDevice(_vkDevices[0].Handler, &device_info, NULL, &_vkDevice);
	AssertVulkanSuccess(err);

	
}

void VulkanContext::AssertVulkanSuccess(VkResult res)
{
	if (res != VK_SUCCESS)
	{
		throw new Exception("Error Result: %s", this->MapVkResultToString(res));
	}
}

std::vector<VulkanPhysicalDeviceInfo> VulkanContext::GetPhysicalDevices(VkInstance &inst)
{
	std::vector<VulkanPhysicalDeviceInfo> result;
	uint32_t gpu_count = 1;
	VkResult res = vkEnumeratePhysicalDevices(inst, &gpu_count, NULL);
	assert(gpu_count);
	std::vector<VkPhysicalDevice> devs;
	devs.resize(gpu_count);

	res = vkEnumeratePhysicalDevices(inst, &gpu_count, devs.data());
	AssertVulkanSuccess(res);
	
	for (int i=0;i<devs.size();i++)
	{
		VulkanPhysicalDeviceInfo elem;
		elem.Handler = devs[i];
		uint32_t family_count;
		//get physical queues
		vkGetPhysicalDeviceQueueFamilyProperties(elem.Handler, &family_count, NULL);
		assert(family_count >= 1);
		elem.QueueFamilyProperties.resize(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(elem.Handler, &family_count, elem.QueueFamilyProperties.data());
		vkGetPhysicalDeviceMemoryProperties(elem.Handler, &elem.MemoryProperties);
		vkGetPhysicalDeviceProperties(elem.Handler, &elem.GraphicProperties);
		elem.LayerProperties = this->GetDeviceLayerProperties(elem.Handler);
		vkGetPhysicalDeviceFeatures(elem.Handler, &elem.Features);
		result.push_back(elem);
	}

	return result;
}


std::vector<LayerProperties> VulkanContext::GetInstanceLayerProperties()
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
	VkLayerProperties *vk_props=NULL;
	VkResult res;
	uint32_t instance_layer_count = 0;
	do {
		 res = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
		AssertVulkanSuccess(res);

		if (instance_layer_count == 0) {
			return std::vector<LayerProperties>();
		}

		vk_props = (VkLayerProperties *)realloc(vk_props, instance_layer_count * sizeof(VkLayerProperties));

		res = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props);
	} while (res == VK_INCOMPLETE);

	/*
	* Now gather the extension list for each instance layer.
	*/
	std::vector<LayerProperties> result;

	for (uint32_t i = 0; i < instance_layer_count; i++) {
		LayerProperties elem;
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

std::vector<LayerProperties> VulkanContext::GetDeviceLayerProperties(VkPhysicalDevice dev)
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
	uint32_t device_layer_count = 0;
	do {
		res = vkEnumerateDeviceLayerProperties(dev,&device_layer_count, NULL);
		AssertVulkanSuccess(res);

		if (device_layer_count == 0) {
			return std::vector<LayerProperties>();
		}

		vk_props = (VkLayerProperties *)realloc(vk_props, device_layer_count * sizeof(VkLayerProperties));

		res = vkEnumerateDeviceLayerProperties(dev,&device_layer_count, vk_props);
	} while (res == VK_INCOMPLETE);

	/*
	* Now gather the extension list for each instance layer.
	*/
	std::vector<LayerProperties> result;

	for (uint32_t i = 0; i < device_layer_count; i++) {
		LayerProperties elem;
		elem.layer = vk_props[i];


		do {
			uint32_t device_extension_count;
			res = vkEnumerateDeviceExtensionProperties(dev,elem.layer.layerName, &device_extension_count, NULL);
			AssertVulkanSuccess(res);

			if (device_extension_count != 0) {
				elem.extensions.resize(device_extension_count);
				res = vkEnumerateDeviceExtensionProperties(dev,elem.layer.layerName, &device_extension_count, elem.extensions.data());
			}
			result.push_back(elem);
		} while (res == VK_INCOMPLETE);
	}
	free(vk_props);
	return result;
}


std::string VulkanContext::MapVkResultToString(VkResult result)
{
	static std::map<int, std::string> map;
	if (map.size() == 0)
	{
		map[VK_SUCCESS] = "VK_SUCCESS";
		map[VK_NOT_READY] = "VK_NOT_READY";
		map[VK_TIMEOUT] = "VK_TIMEOUT";
		map[VK_EVENT_SET] = "VK_EVENT_SET";
		map[VK_EVENT_RESET] = "VK_EVENT_RESET";
		map[VK_INCOMPLETE] = "VK_INCOMPLETE";
		map[VK_ERROR_OUT_OF_HOST_MEMORY] = "VK_ERROR_OUT_OF_HOST_MEMORY";
		map[VK_ERROR_OUT_OF_DEVICE_MEMORY] = "VK_ERROR_OUT_OF_DEVICE_MEMORY";
		map[VK_ERROR_INITIALIZATION_FAILED] = "VK_ERROR_INITIALIZATION_FAILED";
		map[VK_ERROR_DEVICE_LOST] = "VK_ERROR_DEVICE_LOST";
		map[VK_ERROR_MEMORY_MAP_FAILED] = "VK_ERROR_MEMORY_MAP_FAILED";
		map[VK_ERROR_LAYER_NOT_PRESENT] = "VK_ERROR_LAYER_NOT_PRESENT";
		map[VK_ERROR_EXTENSION_NOT_PRESENT] = "VK_ERROR_EXTENSION_NOT_PRESENT";
		map[VK_ERROR_FEATURE_NOT_PRESENT] = "VK_ERROR_FEATURE_NOT_PRESENT";
		map[VK_ERROR_INCOMPATIBLE_DRIVER] = "VK_ERROR_INCOMPATIBLE_DRIVER";
		map[VK_ERROR_TOO_MANY_OBJECTS] = "VK_ERROR_TOO_MANY_OBJECTS";
		map[VK_ERROR_FORMAT_NOT_SUPPORTED] = "VK_ERROR_FORMAT_NOT_SUPPORTED";
		map[VK_ERROR_FRAGMENTED_POOL] = "VK_ERROR_FRAGMENTED_POOL";
		map[VK_ERROR_SURFACE_LOST_KHR] = "VK_ERROR_SURFACE_LOST_KHR";
		map[VK_ERROR_NATIVE_WINDOW_IN_USE_KHR] = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
		map[VK_SUBOPTIMAL_KHR] = "VK_SUBOPTIMAL_KHR";
		map[VK_ERROR_OUT_OF_DATE_KHR] = "VK_ERROR_OUT_OF_DATE_KHR";
		map[VK_ERROR_INCOMPATIBLE_DISPLAY_KHR] = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
		map[VK_ERROR_VALIDATION_FAILED_EXT] = "VK_ERROR_VALIDATION_FAILED_EXT";
		map[VK_ERROR_INVALID_SHADER_NV] = "VK_ERROR_INVALID_SHADER_NV";
		map[VK_ERROR_OUT_OF_POOL_MEMORY_KHR] = "VK_ERROR_OUT_OF_POOL_MEMORY_KHR";
		map[VK_ERROR_INVALID_EXTERNAL_HANDLE_KHX] = "VK_ERROR_INVALID_EXTERNAL_HANDLE_KHX";
		map[VK_RESULT_BEGIN_RANGE] = "VK_RESULT_BEGIN_RANGE";
		map[VK_RESULT_END_RANGE] = "VK_RESULT_END_RANGE";
		map[VK_RESULT_RANGE_SIZE] = "VK_RESULT_RANGE_SIZE";
		map[VK_RESULT_MAX_ENUM] = "VK_RESULT_MAX_ENUM";
	}
	return map[result];
}

