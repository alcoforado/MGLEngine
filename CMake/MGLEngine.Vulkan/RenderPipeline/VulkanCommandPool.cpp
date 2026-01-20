#include "VulkanCommandPool.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../VulkanContext/VulkanPhysicalDevice.h"
#include "VulkanCommandBuffer.h"
#include <MGLEngine.Vulkan/VulkanUtils.h>

VulkanCommandPool::VulkanCommandPool(const VulkanLogicalDevice& device)
	:_logicalDevice(device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = device.GetPhysicalDevice().FindQueueFamilyIndex([](auto family) {
		return family.IsGraphic;
	});
	poolInfo.flags = 0; 

	auto result=vkCreateCommandPool(device.GetHandle(), &poolInfo, nullptr, &_vkPool);
	AssertVulkanSuccess(result);
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(_logicalDevice.GetHandle(), _vkPool, nullptr);
}

VulkanCommandBuffer* VulkanCommandPool::CreateCommandBuffer(VulkanCommandBufferOptions options)
{
	auto result=new VulkanCommandBuffer(this,&options);
	return result;
}
