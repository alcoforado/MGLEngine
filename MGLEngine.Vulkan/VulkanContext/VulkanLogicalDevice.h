#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "VulkanAllocatedQueue.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"
struct GLFWwindow;
class VulkanLogicalDevice
{
	friend VulkanPhysicalDevice;
private:
	VkDevice _vkDevice;
	VulkanSurface  _surface;
	const VulkanPhysicalDevice &_physicalDevice;
	std::vector<std::string> _enabledExtensions;
	std::vector<VulkanAllocatedQueue> _queues;
	std::vector<VkImage> _images;
	


	VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice);
	
public:

	VulkanLogicalDevice & operator=(const VulkanLogicalDevice&) = delete;
	VulkanLogicalDevice(const VulkanLogicalDevice&) = delete;
	

	~VulkanLogicalDevice();
	VkDevice GetHandle() const { return _vkDevice; }
	VulkanSurface& GetSurface() { return _surface; }
	const VulkanPhysicalDevice& GetPhysicalDevice() const { return _physicalDevice; }
	const VulkanAllocatedQueue& GetGraphicQueue() const;
	void WaitToBeIdle() const;
};

