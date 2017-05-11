#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "AllocatedQueue.h"
#include "VulkanSurface.h"
class VulkanPhysicalDevice;
struct GLFWwindow;
class VulkanLogicalDevice
{
	friend VulkanPhysicalDevice;
private:
	VkDevice _vkDevice;
	VulkanSurface  _surface;
	const VulkanPhysicalDevice &_physicalDevice;
	std::vector<std::string> _enabledExtensions;
	std::vector<AllocatedQueue> _queues;

	void CreateSwapChain();
	VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice);
	
public:
	~VulkanLogicalDevice();
	VkDevice GetHandle() const { return _vkDevice; }
	const VulkanSurface& GetSurface() const { return _surface; }
};

