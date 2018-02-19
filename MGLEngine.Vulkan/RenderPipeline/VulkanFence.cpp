#include "VulkanFence.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include "VulkanPipeline.h"


VulkanFence::VulkanFence(VulkanLogicalDevice *dev)
{
	_dev = dev;
	VkFenceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	info.pNext = nullptr;
	info.flags = 0;
	auto result=vkCreateFence(_dev->GetHandle(), &info, VK_NULL_HANDLE, &_fence);
	AssertVulkanSuccess(result);
}


VulkanFence::~VulkanFence()
{
	vkDestroyFence(_dev->GetHandle(),_fence,VK_NULL_HANDLE);
}


