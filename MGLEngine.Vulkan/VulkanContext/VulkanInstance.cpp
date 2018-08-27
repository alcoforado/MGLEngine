#include "VulkanInstance.h"
#include "../vulkanutils.h"
#include  <Utils/Exception.h>
#include <glfw/glfw3.h>
#include <cassert>
#include <MGLEngine.Shared/Utils/eassert.h>
#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
//#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

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
		return true;
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


const char* VulkanInstance::LUNAR_VALIDATION_LAYER = "VK_LAYER_LUNARG_standard_validation";
const char* VulkanInstance::DEBUG_REPORT_EXTENSION = "VK_EXT_debug_report";



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
	
	eassert(this->SupportLayer("VK_LAYER_LUNARG_standard_validation"), "Vulkan Instance does not support VK_LAYER_LUNARG_standard_validation");
	vulkan_layers.push_back(LUNAR_VALIDATION_LAYER);
	vulkan_extensions.push_back(DEBUG_REPORT_EXTENSION);
#endif


	//Set Application Info
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = nullptr;
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
	inst_info.enabledLayerCount = (uint32_t)vulkan_layers.size();
	inst_info.ppEnabledLayerNames = vulkan_layers.data();
	inst_info.enabledExtensionCount = (uint32_t)vulkan_extensions.size();
	inst_info.ppEnabledExtensionNames = vulkan_extensions.data();


	VkResult err;
	err = vkCreateInstance(&inst_info, nullptr, &(this->_vkInstance));
	if (err == VK_ERROR_INCOMPATIBLE_DRIVER) {
		throw new Exception("Cannot create Vulkan instance.\n");
	}
	else if (err) {
		throw new Exception("Vulkan initialization failed with error %s", MapVkResultToString(err).c_str());;
	}

#ifdef _DEBUG
	VkDebugReportCallbackCreateInfoEXT dbg_info;
	memset(&dbg_info, 0, sizeof(dbg_info));
	dbg_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	dbg_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT;
	dbg_info.pfnCallback = DbgCallback;


	auto f=(PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(this->_vkInstance, "vkCreateDebugReportCallbackEXT");
	eassert(f, "Unable to fo find vkCreateDebugReportCallbackEXT function.");
	f(this->_vkInstance, &dbg_info, nullptr, &_vk_debug_report_callback_ext);
	


#endif

	AssertionFailureException::SetOutput(&vulkanError);


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

bool VulkanInstance::SupportLayer(std::string layerName) const
{
	for (const VulkanLayerProperties& elem : _vkLayers)
	{
		if (elem.getName() == layerName)
			return true;
	}
	return false;
}

VulkanInstance::VulkanVersion VulkanInstance::GetVulkanVersion() const
{
	uint32_t api_version;

	int err = vkEnumerateInstanceVersion(&api_version);

	VulkanVersion result;
	result.Major = VK_VERSION_MAJOR(api_version);
	result.Minor = VK_VERSION_MINOR(api_version);
	result.Version = api_version;
	return result;
}
