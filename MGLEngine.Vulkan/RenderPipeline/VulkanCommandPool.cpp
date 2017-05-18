#include "VulkanCommandPool.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../VulkanContext/VulkanPhysicalDevice.h"

VulkanCommandPool::VulkanCommandPool(const VulkanLogicalDevice& device)
	:_logicalDevice(device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = device.GetPhysicalDevice().FindGraphicsQueueIndex();
	poolInfo.flags = 0; 

	vkCreateCommandPool(device.GetHandle(), &poolInfo, nullptr, &_vkPool);
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(_logicalDevice.GetHandle(), _vkPool, nullptr);
}
