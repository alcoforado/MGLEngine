#include "VulkanAllocatedQueue.h"
#include "VulkanLogicalDevice.h"
#include "MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h"

VulkanAllocatedQueue::VulkanAllocatedQueue(const VulkanLogicalDevice& logicalDevice, int familyIndex, int queueIndex)
	:_logicalDevice(logicalDevice),_familyIndex(familyIndex),_queueIndex(queueIndex)
{
	vkGetDeviceQueue(_logicalDevice.GetHandle(), _familyIndex, _queueIndex,&_handle);
}

VulkanAllocatedQueue::~VulkanAllocatedQueue()
{
}

void VulkanAllocatedQueue::Submit(VulkanCommandBuffer &cb) const
{
	VkSubmitInfo submitInfo = {};

	VkCommandBuffer cbh=cb.GetHandle();
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cbh;

	VkResult result=vkQueueSubmit(_handle, 1, &submitInfo, VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}

void VulkanAllocatedQueue::WaitIdle() const
{
	VkResult result= vkQueueWaitIdle(_handle);
	AssertVulkanSuccess(result);
}

