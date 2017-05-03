#include "VulkanContext.h"
#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>
#include <Utils/Exception.h>
#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <map>
VulkanContext::VulkanContext()
{

}


VulkanContext::~VulkanContext()
{
}



static  VkBool32 __stdcall DbgCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
	size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
	void *pUserData) {
	int size = strlen(pMsg) + 100;
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

	printf("%s\n", message);
	fflush(stdout);
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

#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

void VulkanContext::Initialize(GLFWWindow * window)
{
	//Set Application Info
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = NULL;
	app_info.pApplicationName = "MGLEngine";
	app_info.applicationVersion = 1;
	app_info.pEngineName = "MGLEngine";
	app_info.engineVersion = 1;
	app_info.apiVersion = VK_API_VERSION_1_0;

	//Get Extensions needed by GLFW
	uint32_t extensions_count;
	const char** extensions = glfwGetRequiredInstanceExtensions(&extensions_count);

	VkInstanceCreateInfo inst_info = {};
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = 0;
	inst_info.ppEnabledLayerNames = NULL;
	inst_info.enabledExtensionCount = extensions_count;
	inst_info.ppEnabledExtensionNames = extensions;


	VkDebugReportCallbackCreateInfoEXT dbg_info;
	memset(&dbg_info, 0, sizeof(dbg_info));
	dbg_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	dbg_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
	dbg_info.pfnCallback = DbgCallback;
	inst_info.pNext = &dbg_info;




	VkResult err;
	err = vkCreateInstance(&inst_info, NULL, &(this->_vkInstance));
	if (err == VK_ERROR_INCOMPATIBLE_DRIVER) {
		throw new Exception("Cannot create Vulkan instance.\n");
	}
	else if (err) {
		throw new Exception("Vulkan initialization failed with error %s", MapVkResultToString(err).c_str());;
	}


}

std::vector<InstanceLayer> VulkanContext::GetLayerProperties()
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
	do {
		res = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
		if (res) return res;

		if (instance_layer_count == 0) {
			return VK_SUCCESS;
		}

		vk_props = (VkLayerProperties *)realloc(vk_props, instance_layer_count * sizeof(VkLayerProperties));

		res = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props);
	} while (res == VK_INCOMPLETE);

	/*
	* Now gather the extension list for each instance layer.
	*/
	for (uint32_t i = 0; i < instance_layer_count; i++) {
		layer_properties layer_props;
		layer_props.properties = vk_props[i];
		res = init_global_extension_properties(layer_props);
		if (res) return res;
		info.instance_layer_properties.push_back(layer_props);
	}
	free(vk_props);

	return res;
	return std::vector<InstanceLayer>();
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
