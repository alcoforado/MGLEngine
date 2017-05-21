#include "VulkanCommandBuffer.h"
#include "VulkanCommandPool.h"
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../RenderPipeline/VulkanRenderPass.h"
#include <glm/vec4.hpp>
#include "VulkanSwapChainFramebuffers.h"
#include "../VulkanUtils.h"
#include "VulkanPipeline.h"
#include "Utils/Exception.h"
class VulkanRenderPass;

void VulkanCommandBuffer::AssertIsOpen()
{
	if (!_isOpen)
	{
		throw new Exception("Command Buffer is already closed, make sure you add the command before calling VulkanCommandBuffer::End()");

	}
}

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanCommandPool *pool)
	:_pPool(pool),
	_lock(_pPool->GetLogicalDevice())
{
	_pipeline = nullptr;
	_pSubmitInfoCache = nullptr;
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _pPool->GetHandle();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	auto err = vkAllocateCommandBuffers(_pPool->GetLogicalDevice().GetHandle(), &allocInfo, &_vkCommandBuffer);
	AssertVulkanSuccess(err);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	beginInfo.pInheritanceInfo = nullptr; // Optional
	vkBeginCommandBuffer(_vkCommandBuffer, &beginInfo);

	_isOpen = true;
}

VulkanCommandBuffer& VulkanCommandBuffer::BeginRenderPass(VulkanFramebuffer framebuffer, glm::vec4 color)
{
	AssertIsOpen();
	VkClearValue cl = { color.x,color.y,color.z,color.w };
	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = framebuffer.GetRenderPass().GetHandle();
	renderPassInfo.framebuffer = framebuffer.GetHandle();;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = framebuffer.GetSwapChain().GetExtent();
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &cl;

	vkCmdBeginRenderPass(_vkCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::Draw(
	uint32_t  vertexCount, 
	uint32_t instanceCount,
	uint32_t firstVertex,
	uint32_t firstInstance)
{
	AssertIsOpen();
	vkCmdDraw(_vkCommandBuffer,vertexCount, instanceCount, firstVertex, firstInstance);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindPipeline(const VulkanPipeline* pipeline)
{
	AssertIsOpen();
	if (_pipeline != nullptr)
		throw new Exception("CommandBuffer is already assigned to a pipeline");
	
	vkCmdBindPipeline(_vkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->GetHandle());
	_pipeline = pipeline;
	return *this;
}

void VulkanCommandBuffer::End()
{
	auto err = vkEndCommandBuffer(_vkCommandBuffer);
	AssertVulkanSuccess(err);
}

void VulkanCommandBuffer::EndRenderPass()
{
	vkCmdEndRenderPass(_vkCommandBuffer);
}


const VulkanSemaphore& VulkanCommandBuffer::SubmitPipelineAsync(const VulkanSemaphore &wait, VkPipelineStageFlagBits pipelineStage)
{
	auto hw = wait.GetHandle();
	VkPipelineStageFlags waitStages[] = { static_cast<VkFlags>(pipelineStage) };
	VkSemaphore signalSemaphores[] = { _lock.GetHandle() };
	if (_pSubmitInfoCache == nullptr)
	{
		
		if (_pipeline == nullptr)
		{
			throw new Exception("No pipeline is assigned to buffer command, use the methods ::BindPipeline before submission");
		}
		if (_pSubmitInfoCache == nullptr)
		{
			_pSubmitInfoCache = new VkSubmitInfo();
			VkSubmitInfo &submitInfo = *_pSubmitInfoCache;
			submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &_vkCommandBuffer;
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = signalSemaphores;
		}
	}
	_pSubmitInfoCache->pWaitSemaphores = &hw;
	auto err = vkQueueSubmit(_pipeline->GetSwapChain().GetLogicalDevice().GetGraphicQueue().GetHandle(), 1,_pSubmitInfoCache, VK_NULL_HANDLE);
	AssertVulkanSuccess(err);

	return _lock;

}



VulkanCommandBuffer::~VulkanCommandBuffer()
{
	vkFreeCommandBuffers(_pPool->GetLogicalDevice().GetHandle(), _pPool->GetHandle(), 1, &_vkCommandBuffer);
}

