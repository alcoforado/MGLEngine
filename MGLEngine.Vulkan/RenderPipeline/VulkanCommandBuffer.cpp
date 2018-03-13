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

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanCommandPool *pool,VulkanCommandBufferOptions *options)
	:_pPool(pool)
{
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
	beginInfo.flags = options->_bufferUsageFlag;
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
	_statistics.ActionCommands++;
	AssertIsOpen();
	vkCmdDraw(_vkCommandBuffer,vertexCount, instanceCount, firstVertex, firstInstance);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindPipeline(const VulkanPipeline* pipeline)
{
	AssertIsOpen();
	
	vkCmdBindPipeline(_vkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->GetHandle());
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

VulkanCommandBuffer& VulkanCommandBuffer::CopyBuffers(VkBuffer src, VkBuffer dst, long size)
{
	_statistics.TransferCommands++;

	VkBufferCopy copyRegion = {};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = size;
	vkCmdCopyBuffer( _vkCommandBuffer, src,dst,1, &copyRegion);
	return *this;
}

