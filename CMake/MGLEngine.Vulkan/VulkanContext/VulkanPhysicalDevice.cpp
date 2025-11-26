#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include "../VulkanUtils.h"
#include <cassert>
#include <MGLEngine.Shared/Utils/Exception.h>
#include <glfw/glfw3.h>

VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanInstance& inst, VkPhysicalDevice handler)
	:_vulkanInstance(inst)
{
	_handler = handler;
	this->ComputeMemoryProperties();
	this->ComputeFamilyQueues();
	this->ComputeLayers();
	vkGetPhysicalDeviceProperties(_handler, &_graphicProperties);
	vkGetPhysicalDeviceFeatures(_handler, &_features);

	_graphic_family_index=this->FindQueueFamilyIndex([](auto family) {
		return family.IsGraphic;
	});
}

#pragma region Private Methods

void VulkanPhysicalDevice::ComputeLayers()
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
	std::vector<VkLayerProperties> vk_props;
	VkResult res;
	uint32_t device_layer_count = 0;
	do {
		res = vkEnumerateDeviceLayerProperties(dev, &device_layer_count, NULL);
		AssertVulkanSuccess(res);

		if (device_layer_count == 0) {
			return;
		}

		vk_props.resize(device_layer_count);

		res = vkEnumerateDeviceLayerProperties(dev, &device_layer_count, vk_props.data());
	} while (res == VK_INCOMPLETE);

	/*
	* Now gather the extension list for each instance layer.
	*/
	_layers.clear();
	for (uint32_t i = 0; i < device_layer_count; i++) {
		
			
			uint32_t device_extension_count;
			std::vector<VkExtensionProperties>  extend_props;
			res = vkEnumerateDeviceExtensionProperties(dev, vk_props[i].layerName, &device_extension_count, NULL);
			AssertVulkanSuccess(res);

			if (device_extension_count != 0) {
				extend_props.resize(device_extension_count);
				res = vkEnumerateDeviceExtensionProperties(dev, vk_props[i].layerName, &device_extension_count, extend_props.data());
				AssertVulkanSuccess(res);
			}
			MVulkanLayer vulkanLayer(vk_props[i],extend_props);
			_layers.push_back(vulkanLayer);
		
	}
}


void VulkanPhysicalDevice::ComputeFamilyQueues()
{
	uint32_t family_count = 0;
	//get physical queues
	vkGetPhysicalDeviceQueueFamilyProperties(_handler, &family_count, NULL);
	assert(family_count >= 1);
	std::vector<VkQueueFamilyProperties> queueFamilyPropertiesLocal;
	queueFamilyPropertiesLocal.resize(family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(_handler, &family_count, queueFamilyPropertiesLocal.data());

	for(int i=0;i< queueFamilyPropertiesLocal.size();i++)
	{
		auto& queueFamily = queueFamilyPropertiesLocal[i];
		VulkanQueueFamily result = {
			.queueFlags = queueFamily.queueFlags,
			.numberOfQueues = queueFamily.queueCount,
			.timestampValidBits = queueFamily.timestampValidBits,
			.index=(unsigned int) i,
			.minImageTransferGranularity = queueFamily.minImageTransferGranularity,
			.IsGraphic = (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0,
			.IsCompute = (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) != 0,
			.IsTransfer = (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) != 0,
			.IsSparseBinding = (queueFamily.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0,
			.IsProtected = (queueFamily.queueFlags & VK_QUEUE_PROTECTED_BIT) != 0,
			.IsVideoDecode = (queueFamily.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR) != 0,
			.IsVideoEncode = (queueFamily.queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) != 0,
			.IsOpticalFlow = (queueFamily.queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV) != 0,
			.IsDataGraph = (queueFamily.queueFlags & VK_QUEUE_DATA_GRAPH_BIT_ARM) != 0,
			.SupportPresentation = glfwGetPhysicalDevicePresentationSupport(_vulkanInstance.GetHandle(), _handler, i) == GLFW_TRUE
		};


		this->_queueFamilies.push_back(result);
	}
}

void VulkanPhysicalDevice::ComputeMemoryProperties() {
	VkPhysicalDeviceMemoryProperties _memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(_handler, &_memoryProperties);
	for (uint32_t i = 0; i < _memoryProperties.memoryTypeCount; i++)
	{
		_memProperties.push_back(
			VulkanMemoryProperties(
				_memoryProperties.memoryTypes[i].propertyFlags,
				_memoryProperties.memoryHeaps[_memoryProperties.memoryTypes[i].heapIndex]));
	}

}

#pragma endregion




int32_t VulkanPhysicalDevice::FindMemoryPropertyIndex(std::function<bool(const VulkanMemoryProperties& memory)> selector) const
{
	for (uint32_t i = 0; _memProperties.size(); i++)
	{
		if (selector(_memProperties[i]))
		{
			return i;
		}
	}
	return -1;
}

int32_t VulkanPhysicalDevice::FindQueueFamilyIndex(std::function<bool(const VulkanQueueFamily& family)> selector) const
{
	for (uint32_t i = 0; _queueFamilies.size(); i++)
	{
		if (selector(_queueFamilies[i]))
		{
			return i;
		}
	}
	return -1;
}

bool VulkanPhysicalDevice::HasGhraphicsQueue() const
{
	return this->FindQueueFamilyIndex([](auto family) {
		return family.IsGraphic;
	}) != -1;
}
bool VulkanPhysicalDevice::HasComputeQueue() const
{
	return this->FindQueueFamilyIndex([](auto family) {
		return family.IsCompute;
	}) != -1;
}

VkSurfaceCapabilitiesKHR VulkanPhysicalDevice::GetCapabilitiesForSurface(VulkanSurface &surface) const
{
	VkSurfaceCapabilitiesKHR result;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->GetHandle(), surface.GetHandle(), &result);

	return result;
}

std::vector<VkSurfaceFormatKHR> VulkanPhysicalDevice::GetCompatibleSurfaceFormats(VulkanSurface &surface) const
{
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(GetHandle(), surface.GetHandle(), &formatCount, nullptr);
	std::vector<VkSurfaceFormatKHR> formats;
	if (formatCount != 0) {
		formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(GetHandle(), surface.GetHandle(), &formatCount, formats.data());
	}
	return formats;
	
}

std::vector<VkPresentModeKHR> VulkanPhysicalDevice::GetPresentModes(VulkanSurface& surface) const
{

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_handler, surface.GetHandle(), &presentModeCount, nullptr);
	std::vector<VkPresentModeKHR> result;
	if (presentModeCount != 0) {
		result.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_handler, surface.GetHandle(), &presentModeCount, result.data());
	}
	return result;
	
}

bool VulkanPhysicalDevice::IsFormatCompatibleWithSurface(VulkanSurface& surface, VkSurfaceFormatKHR format)
{
	auto formats=GetCompatibleSurfaceFormats(surface);
	for (auto& f : formats)
	{
		if (f.format == format.format && f.colorSpace == format.colorSpace)
		{
			return true;
		}
	}
	return false;
}

bool VulkanPhysicalDevice::IsPresentModeAvailableForSurface(VulkanSurface& surface, VkPresentModeKHR format)
{
	auto presentModes = GetPresentModes(surface);
	for (auto& f : presentModes)
	{
		if (f == format)
		{
			return true;
		}
	}
	return false;
}





bool VulkanPhysicalDevice::IsDiscrete() const {
	return (_graphicProperties.deviceType&VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}

bool VulkanPhysicalDevice::IsIntegrated() const {
	return (_graphicProperties.deviceType & VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
} 
bool VulkanPhysicalDevice::IsCPU() const {
	return (_graphicProperties.deviceType & VK_PHYSICAL_DEVICE_TYPE_CPU) == VK_PHYSICAL_DEVICE_TYPE_CPU;
}
bool VulkanPhysicalDevice::IsVirtual() const {
	return (_graphicProperties.deviceType & VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU) == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU;
}
	 
