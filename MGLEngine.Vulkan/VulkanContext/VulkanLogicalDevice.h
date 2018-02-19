#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "VulkanQueue.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"
#include <MGLEngine.Shared/Utils/opointer.h>
class VulkanCommandPool;

struct GLFWwindow;
class VulkanLogicalDevice
{
	friend VulkanPhysicalDevice;
private:
	VkDevice _vkDevice;
	const VulkanPhysicalDevice &_physicalDevice;
	std::vector<std::string> _enabledExtensions;
	std::vector<VulkanQueue> _queues;
	std::vector<VkImage> _images;
	OPointer<VulkanCommandPool> _pCommandPool;


	VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice);
	
public:

	VulkanLogicalDevice & operator=(const VulkanLogicalDevice&) = delete;
	VulkanLogicalDevice(const VulkanLogicalDevice&) = delete;
	

	~VulkanLogicalDevice();
	VkDevice GetHandle() const { return _vkDevice; }
	const VulkanPhysicalDevice& GetPhysicalDevice() const { return _physicalDevice; }
	const VulkanQueue* GetGraphicQueue() const;

	VulkanCommandPool* GetGraphicCommandPool();
	void WaitToBeIdle() const;
	VulkanFence* CreateFence(bool b = false) const;
};

