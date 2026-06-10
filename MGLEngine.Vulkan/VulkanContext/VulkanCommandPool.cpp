#include "VulkanCommandPool.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../VulkanContext/VulkanPhysicalDevice.h"
#include "VulkanCommandBuffer.h"
#include <MGLEngine.Vulkan/VulkanUtils.h>
#include <memory>
VulkanCommandPool::VulkanCommandPool(const VulkanLogicalDevice& device)
	:_logicalDevice(device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = device.GetPhysicalDevice().GetGraphicFamilyQueueIndex();
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	auto result=vkCreateCommandPool(device.GetHandle(), &poolInfo, nullptr, &_vkPool);
	AssertVulkanSuccess(result);
}

VulkanCommandPool::VulkanCommandPool(const VulkanQueue& queue)
	:_logicalDevice(queue.GetLogicalDevice())
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queue.GetQueueIndex();
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	auto result = vkCreateCommandPool(queue.GetLogicalDevice().GetHandle(), &poolInfo, nullptr, &_vkPool);
	AssertVulkanSuccess(result);
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(_logicalDevice.GetHandle(), _vkPool, nullptr);
}
