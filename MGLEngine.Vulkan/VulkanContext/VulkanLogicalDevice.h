#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "AllocatedQueue.h"
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
	std::vector<AllocatedQueue> _queues;
	VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice);
public:
	~VulkanLogicalDevice();
	VkDevice GetHandle() const { return _vkDevice; }
	VkSurfaceKHR GetSurface() const { return _vkSurface; }
};

