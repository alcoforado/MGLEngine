#include "VulkanSemaphore.h"
#include <vulkan/vulkan.h>
#include "VulkanContext/VulkanLogicalDevice.h"
#include "VulkanUtils.h"


VulkanSemaphore::VulkanSemaphore(const VulkanLogicalDevice &logicalDevice)
	:_logicalDevice(logicalDevice)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	auto err = vkCreateSemaphore(logicalDevice.GetHandle(), &semaphoreInfo, nullptr, &_vkSemaphore);
	AssertVulkanSuccess(err);
}


VulkanSemaphore::~VulkanSemaphore()
{
	vkDestroySemaphore(_logicalDevice.GetHandle(),_vkSemaphore,nullptr);
}
