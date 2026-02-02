#include "VulkanCommandBuffer.h"
#include "VulkanCommandPool.h"
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../RenderPipeline/VulkanRenderPass.h"
#include <glm/vec4.hpp>
#include "VulkanSwapChainFramebuffers.h"
#include "../VulkanUtils.h"
#include "VulkanPipeline.h"
#include <MGLEngine.Shared/Utils/Exception.h>
class VulkanRenderPass;

void VulkanCommandBuffer::AssertIsOpen()
{
	if (!_isOpen)
	{
		throw new Exception("Command Buffer is already closed, make sure you add the command before calling VulkanCommandBuffer::End()");

	}
}

VulkanCommandBuffer& VulkanCommandBuffer::Reset()
{
	auto err = vkResetCommandBuffer(_vkCommandBuffer, 0);
	AssertVulkanSuccess(err);
	_isOpen = false;
	return *this;
}

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanCommandPool *pool)
	:_pPool(pool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _pPool->GetHandle();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	auto err = vkAllocateCommandBuffers(_pPool->GetLogicalDevice().GetHandle(), &allocInfo, &_vkCommandBuffer);
	AssertVulkanSuccess(err);

	
}

VulkanCommandBuffer& VulkanCommandBuffer::Begin(bool asyncQueues,bool oneSubmissionPerReset )
{
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	if (asyncQueues)
	{
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	}
	if (oneSubmissionPerReset)
	{
		beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	}
	beginInfo.pInheritanceInfo = nullptr; // Optional
	auto result=vkBeginCommandBuffer(_vkCommandBuffer, &beginInfo);
	AssertVulkanSuccess(result);
	_isOpen = true;
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BeginRenderPass(VkRenderPass renderPass, VkFramebuffer framebuffer, VkExtent2D extent,glm::vec4 color)
{
	AssertIsOpen();
	VkClearValue cl = { color.x,color.y,color.z,color.w };
	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = framebuffer;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = extent;
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

VulkanCommandBuffer& VulkanCommandBuffer::DrawIndexed(uint32_t indexCount,uint32_t firstIndex,uint32_t vertexOffset)
{
	AssertIsOpen();
	vkCmdDrawIndexed(_vkCommandBuffer, indexCount, 1, firstIndex, vertexOffset,0);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindGraphicsPipeline( VkPipeline _vkPipeline)
{
	AssertIsOpen();
	
	vkCmdBindPipeline(_vkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _vkPipeline);
	return *this;
}




void VulkanCommandBuffer::End()
{
	auto err = vkEndCommandBuffer(_vkCommandBuffer);
	AssertVulkanSuccess(err);
	_isOpen = false;
}

void VulkanCommandBuffer::EndRenderPass()
{
	vkCmdEndRenderPass(_vkCommandBuffer);
}







 



VulkanCommandBuffer::~VulkanCommandBuffer()
{
	vkFreeCommandBuffers(_pPool->GetLogicalDevice().GetHandle(), _pPool->GetHandle(), 1, &_vkCommandBuffer);

}

VkCommandBuffer VulkanCommandBuffer::GetHandle() const
{
	return _vkCommandBuffer;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindVertexBuffer(VkBuffer buff)
{
	VkDeviceSize off = 0;
	vkCmdBindVertexBuffers(_vkCommandBuffer, 0, 1, &buff,&off);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindIndexBuffer(VkBuffer buff)
{
	vkCmdBindIndexBuffer(_vkCommandBuffer, buff, 0, VK_INDEX_TYPE_UINT32);
	return *this;
}





VulkanCommandBuffer& VulkanCommandBuffer::CopyBuffers(VkBuffer src, VkBuffer dst, long size)
{

	VkBufferCopy copyRegion = {};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = size;
	vkCmdCopyBuffer( _vkCommandBuffer, src,dst,1, &copyRegion);
	return *this;
}

