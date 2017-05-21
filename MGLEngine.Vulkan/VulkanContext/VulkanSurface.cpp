#include "VulkanSurface.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "../VulkanUtils.h"
#include <cassert>
#include <algorithm>


VulkanSurface::VulkanSurface(const VulkanPhysicalDevice& device, GLFWwindow* window)
	:_physicalDevice(device)
{
	VkResult err = glfwCreateWindowSurface(device.GetVulkanInstance().GetHandle(), window, NULL, &_vkSurface);
	AssertVulkanSuccess(err);

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.GetHandle(), _vkSurface, &_capabilities);


	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device.GetHandle(), _vkSurface, &formatCount, nullptr);

	if (formatCount != 0) {
		_formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device.GetHandle(), _vkSurface, &formatCount, _formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device.GetHandle(), _vkSurface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		_presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device.GetHandle(), _vkSurface, &presentModeCount, _presentModes.data());
	}

	this->UpdateWindowDims(window);


}

void VulkanSurface::UpdateWindowDims(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice.GetHandle(), _vkSurface, &_capabilities);
	_windowHeight = static_cast<uint32_t>(height);
	_windowWidth = static_cast<uint32_t>(width);
}


VulkanSurface::~VulkanSurface()
{
	vkDestroySurfaceKHR(_physicalDevice.GetVulkanInstance().GetHandle(), _vkSurface, nullptr);
}

bool VulkanSurface::SupportsFormat(VkFormat format, VkColorSpaceKHR colorSpace) const 
{
	for(int i=0;i<_formats.size();i++)
	{
		if (_formats[i].colorSpace == colorSpace && _formats[i].format == format)
			return true;
	}
	return false;
}

bool VulkanSurface::SupportsPresentation(VkPresentModeKHR present) const
{
	return std::find(_presentModes.begin(), _presentModes.end(), present) != _presentModes.end();

}

bool VulkanSurface::SupportsImageCount(uint32_t i) const
{
	return i > _capabilities.minImageCount && (i < _capabilities.maxImageCount || _capabilities.maxImageCount == 0);
}

VkExtent2D VulkanSurface::GetExtent() const
{
	VkExtent2D extent; 
	
	extent.height = std::min(_windowHeight,_capabilities.currentExtent.height);
	extent.height = std::max(extent.height, _capabilities.minImageExtent.height);

	extent.width = std::min(_windowWidth, _capabilities.currentExtent.width);
	extent.width = std::max(extent.width, _capabilities.minImageExtent.width);

	return _capabilities.currentExtent;
}

std::vector<uint32_t> VulkanSurface::FindQueueFamilyIndicesThatSupportPresentation() const
{
	std::vector<uint32_t> result;
	for (int i = 0; i < _physicalDevice.GetFamilyProperties().size(); i++)
	{
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(_physicalDevice.GetHandle(), i, this->GetHandle(), &presentSupport);
		if (presentSupport)
			result.push_back(i);
	}
	return result;
}

/*
 * Returns a vector of two positions indicating the indices of the Graphics and Presentation Queue.
 * If the families are the same, it returns just a vector of size 1 containing the index of the queue.
 */
PresentationGraphicsFamilyIndices VulkanSurface::GetPresentationAndGraphicsQueusFamilyIndices() const
{
	auto presentations = this->FindQueueFamilyIndicesThatSupportPresentation();
	auto graphic_index = _physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);
	PresentationGraphicsFamilyIndices result;
	if (std::find(presentations.begin(),presentations.end(),graphic_index) != presentations.end())
	{
		result.GraphicQueueFamily = result.PresentationQueueFamily = graphic_index;
	}
	else
	{
		result.GraphicQueueFamily=graphic_index;
		result.PresentationQueueFamily=presentations[0];
	}
	return result;
}
