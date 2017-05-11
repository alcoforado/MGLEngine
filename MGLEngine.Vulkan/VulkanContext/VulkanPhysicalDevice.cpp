#include "VulkanPhysicalDevice.h"
#include "../VulkanUtils.h"
#include <cassert>





std::vector<VulkanLayerProperties> VulkanPhysicalDevice::GetAvailableLayerProperties()
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
	VkPhysicalDevice dev = _handler;
	VkLayerProperties *vk_props = NULL;
	VkResult res;
	uint32_t device_layer_count = 0;
	do {
		res = vkEnumerateDeviceLayerProperties(dev, &device_layer_count, NULL);
		AssertVulkanSuccess(res);

		if (device_layer_count == 0) {
			return std::vector<VulkanLayerProperties>();
		}

		vk_props = (VkLayerProperties *)realloc(vk_props, device_layer_count * sizeof(VkLayerProperties));

		res = vkEnumerateDeviceLayerProperties(dev, &device_layer_count, vk_props);
	} while (res == VK_INCOMPLETE);

	/*
	* Now gather the extension list for each instance layer.
	*/
	std::vector<VulkanLayerProperties> result;

	for (uint32_t i = 0; i < device_layer_count; i++) {
		VulkanLayerProperties elem;
		elem.layer = vk_props[i];


		do {
			uint32_t device_extension_count;
			res = vkEnumerateDeviceExtensionProperties(dev, elem.layer.layerName, &device_extension_count, NULL);
			AssertVulkanSuccess(res);

			if (device_extension_count != 0) {
				elem.extensions.resize(device_extension_count);
				res = vkEnumerateDeviceExtensionProperties(dev, elem.layer.layerName, &device_extension_count, elem.extensions.data());
			}
			result.push_back(elem);
		} while (res == VK_INCOMPLETE);
	}
	free(vk_props);
	return result;
}


VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanInstance& inst,VkPhysicalDevice handler)
	:_vulkanInstance(inst)
{
	_handler = handler;
	uint32_t family_count;
	//get physical queues
	vkGetPhysicalDeviceQueueFamilyProperties(_handler, &family_count, NULL);
	assert(family_count >= 1);
	_queueFamilyProperties.resize(family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(_handler, &family_count, _queueFamilyProperties.data());
	vkGetPhysicalDeviceMemoryProperties(_handler, &_memoryProperties);
	vkGetPhysicalDeviceProperties(_handler, &_graphicProperties);
	_layerProperties = this->GetAvailableLayerProperties();
	vkGetPhysicalDeviceFeatures(_handler, &_features);

}

std::vector<VkQueueFamilyProperties> VulkanPhysicalDevice::FindQueuesWithType(VkFlags flags) const
{
	std::vector<VkQueueFamilyProperties> result;
	for (int i = 0; i < _queueFamilyProperties.size(); i++)
	{
		if (_queueFamilyProperties[i].queueFlags & flags)
		{
			result.push_back(_queueFamilyProperties[i]);
		}
	}
	return result;
}


uint32_t VulkanPhysicalDevice::FindQueueFamilyIndexWithType(VkFlags flags) const
{
	for (int i = 0; i < _queueFamilyProperties.size(); i++)
	{
		if (_queueFamilyProperties[i].queueFlags & flags)
		{
			return i;
		}
	}
	return -1;
}


VulkanLogicalDevice VulkanPhysicalDevice::CreateLogicalDevice(GLFWwindow *window) const
{
	return VulkanLogicalDevice(window, *this);
}

