#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include <Utils/Exception.h>
#include "../VulkanUtils.h"
#include <glfw\glfw3.h>
VulkanLogicalDevice::VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice)
	:_physicalDevice(physicalDevice)
{
	//Create Device with the Queues
	float queue_priorities[1] = { 0.0 };
	std::vector<const char*> device_extensions;
	device_extensions.push_back("VK_KHR_swapchain");
	VkDeviceQueueCreateInfo queue_info;
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.queueCount = 1;
	queue_info.pQueuePriorities = queue_priorities;
	queue_info.queueFamilyIndex = physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);

	VkDeviceCreateInfo device_info = {};
	device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_info.pNext = NULL;
	device_info.queueCreateInfoCount = 1;
	device_info.pQueueCreateInfos = &queue_info;
	device_info.enabledExtensionCount = (uint32_t)device_extensions.size();
	device_info.ppEnabledExtensionNames = device_extensions.data();
	device_info.enabledLayerCount = 0;
	device_info.ppEnabledLayerNames = NULL;
	device_info.pEnabledFeatures = NULL;

	VkInstance inst = physicalDevice.GetVulkanInstance().GetHandle();
	if (!glfwGetPhysicalDevicePresentationSupport(inst, physicalDevice.GetHandler(), physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT)))
	{
		throw new Exception("Vulkan does not support GLFW, Ending application");
	}

	VkResult err = vkCreateDevice(physicalDevice.GetHandler(), &device_info, NULL, &_vkDevice);
	AssertVulkanSuccess(err);
	
	VkSurfaceKHR surface;
	err = glfwCreateWindowSurface(inst, window, NULL, &surface);
	AssertVulkanSuccess(err);
	


}


VulkanLogicalDevice::~VulkanLogicalDevice()
{
}
