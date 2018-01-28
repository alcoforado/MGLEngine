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

void VulkanAllocatedQueue::Submit(const std::vector<VulkanCommandBuffer*>& vcb,VulkanSemaphore *pSignal, VulkanSemaphore *pWait,const std::vector<VkPipelineStageFlagBits>& waitStages) const
{
	std::vector<VkCommandBuffer> _vcbH(vcb.size());
	for (int i=0;i<vcb.size();i++)
	{
		_vcbH[i]= vcb[i]->GetHandle();
	}
	

	VkSemaphore w, s;

	VulkanSemaphore* sm = new VulkanSemaphore(&_logicalDevice);
	VkSubmitInfo submitInfo = {};
	VkSemaphore sHandle = sm->GetHandle();

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = (uint32_t) _vcbH.size();
	submitInfo.pCommandBuffers = _vcbH.data();
	if (pSignal!=nullptr)
	{
		s = pSignal->GetHandle();
		submitInfo.pSignalSemaphores = &s;
		submitInfo.signalSemaphoreCount = 1;
	}
	else if (pWait!=nullptr)
	{
		w = pWait->GetHandle();
		submitInfo.pWaitSemaphores = &w;
		submitInfo.waitSemaphoreCount = 1;
	}
	VkFlags dstStageMask= FromBitFlagsToInt(waitStages);
	submitInfo.pWaitDstStageMask = &dstStageMask;
	
	VkResult result = vkQueueSubmit(_handle, 1, &submitInfo, VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}

void VulkanAllocatedQueue::Submit(VulkanCommandBatchCollection& cl)
{
	VkResult result = vkQueueSubmit(_handle,(uint32_t) cl._submitInfos.size(), cl._submitInfos.data(), VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}

void VulkanAllocatedQueue::WaitIdle() const
{
	VkResult result= vkQueueWaitIdle(_handle);
	AssertVulkanSuccess(result);
}

