#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "VulkanQueue.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"
#include <MGLEngine.Shared/Utils/opointer.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMemoryManager.h>
class VulkanCommandPool;
class VulkanDescriptorSetPool;
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
	OPointer<VulkanDescriptorSetPool> _pDescriptorSetPool;

	VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice);
	
public:

	VulkanLogicalDevice & operator=(const VulkanLogicalDevice&) = delete;
	VulkanLogicalDevice(const VulkanLogicalDevice&) = delete;
	

	~VulkanLogicalDevice();
	VkDevice GetHandle() const { return _vkDevice; }
	const VulkanPhysicalDevice& GetPhysicalDevice() const { return _physicalDevice; }
	const VulkanQueue* GetGraphicQueue() const;

	VulkanCommandPool* GetGraphicCommandPool();
	VulkanDescriptorSetPool* GetDescriptorSetPool() { return _pDescriptorSetPool; }
	void WaitToBeIdle() const;
	VulkanFence* CreateFence(bool b = false) const;
	VulkanSemaphore* CreateSemaphore() const;
};

