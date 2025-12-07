#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include <MGLEngine.Shared/Utils/Exception.h>
#include "../VulkanUtils.h"
#include <glfw\glfw3.h>
#include <algorithm>
#include <cassert>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandPool.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanFence.h>
VulkanLogicalDevice::VulkanLogicalDevice(const VulkanPhysicalDevice &physicalDevice,uint32_t graphicQueueFamilyIndex)
	:_physicalDevice(physicalDevice)
{
	//Create Device with the Queues
	float queue_priorities[1] = { 0.0 };
	std::vector<const char*> device_extensions;
	_enabledExtensions.push_back("VK_KHR_swapchain");




	//Get instance
	auto vkInstanceHandle = physicalDevice.GetVulkanInstance().GetHandle();

	assert(graphicQueueFamilyIndex <  physicalDevice.GetQueueFamilies().size());
	const auto& graphicQueueFamily = physicalDevice.GetQueueFamilies()[graphicQueueFamilyIndex];
	assert(graphicQueueFamily.IsGraphic && graphicQueueFamily.SupportPresentation);

	std::vector<VkDeviceQueueCreateInfo> queues;


	VkDeviceQueueCreateInfo queue_info;
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.queueCount = 1;
	queue_info.pQueuePriorities = queue_priorities;
	queue_info.queueFamilyIndex = graphicQueueFamilyIndex;
	queue_info.flags = 0;
	queues.push_back(queue_info);
	

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
	auto index=_physicalDevice.GetGraphicFamilyQueueIndex();
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
