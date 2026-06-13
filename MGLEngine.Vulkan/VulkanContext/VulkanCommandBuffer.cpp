#include "VulkanCommandBuffer.h"
#include "VulkanCommandPool.h"
#include "../VulkanContext/VulkanLogicalDevice.h"
#include <glm/vec4.hpp>
#include "../VulkanUtils.h"
#include <MGLEngine.Shared/utils.h>
class VulkanRenderPass;

void VulkanCommandBuffer::AssertIsOpen()
{
	if (!_isOpen)
	{
		throw new Exception("Command Buffer is already closed, make sure you add the command before calling VulkanCommandBuffer::End()");

	}
}

void VulkanCommandBuffer::AssertIsNotDisposed() const
{
	eassert(_vkCommandBuffer!= VK_NULL_HANDLE,"CommandBuffer Is Disposed");
	
}

VulkanCommandBuffer& VulkanCommandBuffer::Reset()
{
	AssertIsNotDisposed();
	auto err = vkResetCommandBuffer(_vkCommandBuffer, 0);
	AssertVulkanSuccess(err);
	_isOpen = false;
	return *this;
}

VulkanCommandBuffer::VulkanCommandBuffer(VulkanCommandPool* pool)
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

VulkanCommandBuffer& VulkanCommandBuffer::BeginOnce()
{
	return this->Begin(false, true);


}


VulkanCommandBuffer& VulkanCommandBuffer::Begin(bool simultaneousUsage,bool oneSubmissionPerReset )
{
	AssertIsNotDisposed();
	eassert(!_isOpen, "Buffer already started");
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	if (simultaneousUsage)
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
	AssertIsNotDisposed();
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

VulkanCommandBuffer& VulkanCommandBuffer::SetViewportAndScissor(VkExtent2D extent)
{
	AssertIsOpen();
	AssertIsNotDisposed();
	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(extent.width);
	viewport.height = static_cast<float>(extent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = extent;

	vkCmdSetViewport(_vkCommandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(_vkCommandBuffer, 0, 1, &scissor);

	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::Draw(
	uint32_t  vertexCount, 
	uint32_t instanceCount,
	uint32_t firstVertex,
	uint32_t firstInstance)
{
	AssertIsOpen();
	AssertIsNotDisposed();
	vkCmdDraw(_vkCommandBuffer,vertexCount, instanceCount, firstVertex, firstInstance);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::DrawIndexed(uint32_t indexCount,uint32_t firstIndex,uint32_t vertexOffset)
{
	AssertIsOpen();
	AssertIsNotDisposed();
	vkCmdDrawIndexed(_vkCommandBuffer, indexCount, 1, firstIndex, vertexOffset,0);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindGraphicsPipeline( VkPipeline _vkPipeline)
{
	AssertIsOpen();
	AssertIsNotDisposed();
	vkCmdBindPipeline(_vkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _vkPipeline);
	return *this;
}




void VulkanCommandBuffer::End()
{
	AssertIsOpen();
	AssertIsNotDisposed();
	auto err = vkEndCommandBuffer(_vkCommandBuffer);
	AssertVulkanSuccess(err);
	_isOpen = false;
}

void VulkanCommandBuffer::EndRenderPass()
{
	AssertIsOpen();
	AssertIsNotDisposed();
	vkCmdEndRenderPass(_vkCommandBuffer);
}







 

void VulkanCommandBuffer::Dispose() {
	AssertIsNotDisposed();
	vkFreeCommandBuffers(_pPool->GetLogicalDevice().GetHandle(), _pPool->GetHandle(), 1, &_vkCommandBuffer);
	_vkCommandBuffer = VK_NULL_HANDLE;
}

VulkanCommandBuffer::~VulkanCommandBuffer()  
{
	eassert(_vkCommandBuffer == VK_NULL_HANDLE, "Vulkan Command Buffer should be disposed before destruction");

}

VkCommandBuffer VulkanCommandBuffer::GetHandle() const
{
	AssertIsNotDisposed();
	return _vkCommandBuffer;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindVertexBuffer(VkBuffer buff)
{
	AssertIsNotDisposed();
	AssertIsOpen();
	VkDeviceSize off = 0;
	vkCmdBindVertexBuffers(_vkCommandBuffer, 0, 1, &buff,&off);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindIndexBuffer(VkBuffer buff)
{
	AssertIsNotDisposed();
	AssertIsOpen();

	vkCmdBindIndexBuffer(_vkCommandBuffer, buff, 0, VK_INDEX_TYPE_UINT32);
	return *this;
}





VulkanCommandBuffer& VulkanCommandBuffer::CopyBuffers(VkBuffer src, VkBuffer dst, long size)
{
	AssertIsNotDisposed();
	AssertIsOpen();

	VkBufferCopy copyRegion = {};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = size;
	vkCmdCopyBuffer( _vkCommandBuffer, src,dst,1, &copyRegion);
	return *this;
}

