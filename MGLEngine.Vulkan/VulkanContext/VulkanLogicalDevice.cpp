#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include <Utils/Exception.h>
#include "../VulkanUtils.h"
#include <glfw\glfw3.h>
#include <algorithm>
#include <cassert>

void VulkanLogicalDevice::CreateSwapChain()
{
	assert(_surface.SupportsFormat(VK_FORMAT_A8B8G8R8_UNORM_PACK32, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR));
	assert(_surface.SupportsPresentation(VK_PRESENT_MODE_MAILBOX_KHR));
	assert(_surface.SupportsImageCount(3));
	
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = _surface.GetHandle();
	createInfo.minImageCount = 3;
	createInfo.imageFormat = VK_FORMAT_A8B8G8R8_UNORM_PACK32;
	createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	createInfo.imageExtent = _surface.GetExtent();
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	auto pgQueues = _surface.GetPresentationAndGraphicsQueusFamilyIndices();
	std::vector<uint32_t> queues;
	if(pgQueues.GraphicQueueFamily  == pgQueues.PresentationQueueFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	else
	{
		queues.push_back(pgQueues.GraphicQueueFamily);
		queues.push_back(pgQueues.PresentationQueueFamily);
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queues.data();
	}
	
}

VulkanLogicalDevice::VulkanLogicalDevice(GLFWwindow *window,const VulkanPhysicalDevice& physicalDevice)
	:_physicalDevice(physicalDevice),
	 _surface(physicalDevice,window)
{
	//Create Device with the Queues
	float queue_priorities[1] = { 0.0 };
	std::vector<const char*> device_extensions;
	_enabledExtensions.push_back("VK_KHR_swapchain");




	//Get instance
	auto instHandle = physicalDevice.GetVulkanInstance().GetHandle();

	auto familyGraphicsIndex = physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);
	auto presentation_indices= _surface.FindQueueFamilyIndicesThatSupportPresentation();
	auto presentation_index = std::find(presentation_indices.begin(), presentation_indices.end(), familyGraphicsIndex);

	std::vector<VkDeviceQueueCreateInfo> queues;


	VkDeviceQueueCreateInfo queue_info;
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.queueCount = 1;
	queue_info.pQueuePriorities = queue_priorities;
	queue_info.queueFamilyIndex = physicalDevice.FindQueueFamilyIndexWithType(VK_QUEUE_GRAPHICS_BIT);
	queues.push_back(queue_info);
	if (*presentation_index != familyGraphicsIndex)
	{
		queue_info.queueFamilyIndex = *presentation_index;
		queues.push_back(queue_info);
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
			_queues.push_back(AllocatedQueue(*this, queue.queueFamilyIndex, queue_index));
		}
	}

	CreateSwapChain();

}


VulkanLogicalDevice::~VulkanLogicalDevice()
{
}
