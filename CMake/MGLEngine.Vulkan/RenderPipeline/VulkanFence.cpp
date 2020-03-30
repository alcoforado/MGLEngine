#include "VulkanFence.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include "VulkanPipeline.h"
#include <basetsd.h>


VulkanFence::VulkanFence(const VulkanLogicalDevice *dev,bool b)
{
	_dev = dev;
	VkFenceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	info.pNext = nullptr;
	info.flags = b ? VK_FENCE_CREATE_SIGNALED_BIT : 0;
	auto result=vkCreateFence(_dev->GetHandle(), &info, VK_NULL_HANDLE, &_fence);
	AssertVulkanSuccess(result);
}


VulkanFence::~VulkanFence()
{
	vkDestroyFence(_dev->GetHandle(),_fence,VK_NULL_HANDLE);
}

void VulkanFence::Wait() const 
{
	auto result = vkWaitForFences(_dev->GetHandle(), 1, &_fence, VK_TRUE, std::numeric_limits<long unsigned int>::max());
	AssertVulkanSuccess(result);
}

void VulkanFence::Reset() const
{
	VkResult r = vkResetFences(_dev->GetHandle(), 1, &_fence);
	AssertVulkanSuccess(r);
}




