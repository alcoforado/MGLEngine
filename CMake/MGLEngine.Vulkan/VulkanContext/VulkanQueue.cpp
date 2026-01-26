#include "VulkanQueue.h"
#include "VulkanLogicalDevice.h"
#include "MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h"
#include "MGLEngine.Vulkan/RenderPipeline/VulkanFence.h"
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanPhysicalDevice.h>
#include "MGLEngine.Vulkan/VulkanUtils.h"
VulkanQueue::VulkanQueue(const VulkanLogicalDevice& logicalDevice, int familyIndex, int queueIndex)
	:_logicalDevice(logicalDevice),_familyIndex(familyIndex),_queueIndex(queueIndex)
{
	_isPresentationQueue =_logicalDevice.GetPhysicalDevice().GetQueueFamilies()[familyIndex].SupportPresentation;
	_isGraphicQueue = _logicalDevice.GetPhysicalDevice().GetQueueFamilies()[familyIndex].IsGraphic;
	vkGetDeviceQueue(_logicalDevice.GetHandle(), _familyIndex, _queueIndex,&_handle);
}

VulkanQueue::~VulkanQueue()
{
}

void VulkanQueue::Submit(VulkanCommandBuffer &cb) const
{
	VkSubmitInfo submitInfo = {};

	VkCommandBuffer cbh=cb.GetHandle();
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cbh;

	VkResult result=vkQueueSubmit(_handle, 1, &submitInfo, VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}

void VulkanQueue::Submit(const std::vector<VulkanCommandBuffer*>& vcb,VulkanSemaphore *pSignal, VulkanSemaphore *pWait,const std::vector<VkPipelineStageFlagBits>& waitStages,	VulkanFence *fence) const
{
	std::vector<VkCommandBuffer> _vcbH(vcb.size());
	for (int i=0;i<vcb.size();i++)
	{
		_vcbH[i]= vcb[i]->GetHandle();
	}
	

	VkSemaphore w, s;

	
	VkSubmitInfo submitInfo = {};
	

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = (uint32_t) _vcbH.size();
	submitInfo.pCommandBuffers = _vcbH.data();
	if (pSignal!=nullptr)
	{
		s = pSignal->GetHandle();
		submitInfo.pSignalSemaphores = &s;
		submitInfo.signalSemaphoreCount = 1;
	}
	if (pWait!=nullptr)
	{
		w = pWait->GetHandle();
		submitInfo.pWaitSemaphores = &w;
		submitInfo.waitSemaphoreCount = 1;
	}
	VkFlags dstStageMask= BitwiseOr(waitStages);
	submitInfo.pWaitDstStageMask = &dstStageMask;
	
	VkResult result = vkQueueSubmit(_handle, 1, &submitInfo, fence != nullptr ? fence->GetHandle() : VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}



void VulkanQueue::Submit(VulkanCommandBuffer *cb, VulkanSemaphore* pSignal, VulkanSemaphore* pWait, VkPipelineStageFlags waitStages, VulkanFence* fence) const
{
	

	VkSemaphore w, s;


	VkSubmitInfo submitInfo = {};
	auto cbh = cb->GetHandle();

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cbh;
	if (pSignal != nullptr)
	{
		s = pSignal->GetHandle();
		submitInfo.pSignalSemaphores = &s;
		submitInfo.signalSemaphoreCount = 1;
	}
	if (pWait != nullptr)
	{
		w = pWait->GetHandle();
		submitInfo.pWaitSemaphores = &w;
		submitInfo.waitSemaphoreCount = 1;
	}
	VkFlags dstStageMask = waitStages;
	submitInfo.pWaitDstStageMask = &dstStageMask;

	VkResult result = vkQueueSubmit(_handle, 1, &submitInfo, fence != nullptr ? fence->GetHandle() : VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}

void VulkanQueue::Submit(VulkanCommandBatchCollection& cl,VulkanFence *fence) const
{
	VkResult result = vkQueueSubmit(_handle,(uint32_t) cl._submitInfos.size(), cl._submitInfos.data(), fence != nullptr ? fence->GetHandle() : VK_NULL_HANDLE);
	AssertVulkanSuccess(result);
}

void VulkanQueue::Present(VkSwapchainKHR swapChain, uint32_t imageIndex, VulkanSemaphore* toSignal) const
{
	eassert(_isPresentationQueue, "This queue doest not support Presentation");
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	VkSemaphore semaphore = toSignal->GetHandle();
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &semaphore;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapChain;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; //revisit this field if you pass an array of swapchains
	auto err = vkQueuePresentKHR(_handle, &presentInfo);
	AssertVulkanSuccess(err);

}

void VulkanQueue::WaitIdle() const
{
	VkResult result= vkQueueWaitIdle(_handle);
	AssertVulkanSuccess(result);
}

