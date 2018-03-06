#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include <Utils/Exception.h>
#include "../VulkanUtils.h"
#include <glfw\glfw3.h>
#include <algorithm>
#include <cassert>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandPool.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanFence.h>
VulkanLogicalDevice::VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice)
	:_physicalDevice(physicalDevice)
{
	//Create Device with the Queues
	float queue_priorities[1] = { 0.0 };
	std::vector<const char*> device_extensions;
	_enabledExtensions.push_back("VK_KHR_swapchain");




	//Get instance
	auto instHandle = physicalDevice.GetVulkanInstance().GetHandle();

	VulkanSurface surface(physicalDevice, window);
	auto familyGraphicsIndex = physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);
	auto presentation_indices= surface.FindQueueFamilyIndicesThatSupportPresentation();
	auto presentation_index = std::find(presentation_indices.begin(), presentation_indices.end(), familyGraphicsIndex);

	std::vector<VkDeviceQueueCreateInfo> queues;


	VkDeviceQueueCreateInfo queue_info;
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.queueCount = 1;
	queue_info.pQueuePriorities = queue_priorities;
	queue_info.queueFamilyIndex = physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);
	queue_info.flags = 0;
	queues.push_back(queue_info);
	//Add presentaion queue if it is different from the graphic queue.
	if (*presentation_index != familyGraphicsIndex)
	{
		throw new Exception("Graphic queue should be presentation queue");
		//queue_info.queueFamilyIndex = *presentation_index;
		//queues.push_back(queue_info);
	}

	auto enabled_extensions= ConvertToVectorChar(_enabledExtensions);
	VkDeviceCreateInfo device_info = {};
	device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_info.pNext = NULL;
	device_info.queueCreateInfoCount = (uint32_t) queues.size();
	device_info.pQueueCreateInfos = queues.data();
	device_info.enabledExtensionCount = (uint32_t)_enabledExtensions.size();
	device_info.ppEnabledExtensionNames = enabled_extensions.data();
	device_info.enabledLayerCount = 0;
	device_info.ppEnabledLayerNames = NULL;
	device_info.pEnabledFeatures = NULL;

	if (!glfwGetPhysicalDevicePresentationSupport(instHandle, physicalDevice.GetHandle(), physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT)))
	{
		throw new Exception("Vulkan does not support GLFW, Ending application");
	}
	//create device;
	VkResult err = vkCreateDevice(physicalDevice.GetHandle(), &device_info, NULL, &_vkDevice);
	AssertVulkanSuccess(err);

	for (auto queue : queues)
	{
		for (uint32_t queue_index = 0; queue_index < queue.queueCount; queue_index++)
		{
			_queues.push_back(VulkanQueue(*this, queue.queueFamilyIndex, queue_index));
		}
	}


}







VulkanLogicalDevice::~VulkanLogicalDevice()
{
}

const VulkanQueue* VulkanLogicalDevice::GetGraphicQueue() const
{
	auto index=_physicalDevice.FindGraphicsQueueIndex();
	for (int i=0;i<_queues.size();i++)
	{
		if (_queues[i].GetFamilyIndex() == index)
		{
			return &(_queues[i]);
		}
	}
	throw new Exception("No graphic queueu was found");

}

VulkanCommandPool* VulkanLogicalDevice::GetGraphicCommandPool() 
{
	if (_pCommandPool == nullptr)
	{
		_pCommandPool = new VulkanCommandPool(*this);
	}
	return _pCommandPool;
}

void VulkanLogicalDevice::WaitToBeIdle() const
{
	vkDeviceWaitIdle(_vkDevice);
}

VulkanFence* VulkanLogicalDevice::CreateFence(bool b) const
{
	return new VulkanFence(this, b);
}

VulkanSemaphore* VulkanLogicalDevice::CreateSemaphore() const
{
	return new VulkanSemaphore(this);

}
