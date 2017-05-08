#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
class VulkanPhysicalDevice;
struct GLFWwindow;
class VulkanLogicalDevice
{
	friend VulkanPhysicalDevice;
private:
	VkDevice _vkDevice;
	VkSurfaceKHR  _vkSurface;
	const VulkanPhysicalDevice &_physicalDevice;
	std::vector<std::string> _enabledExtensions;
	VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice);
public:
	~VulkanLogicalDevice();

};

