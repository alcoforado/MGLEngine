#include "VulkanCommandBuffer.h"
#include "VulkanCommandPool.h"
#include "../VulkanContext/VulkanLogicalDevice.h"
#include <glm/vec4.hpp>
#include "../VulkanUtils.h"
#include <MGLEngine.Shared/utils.h>
class VulkanRenderPass;

void VulkanCommandBuffer::AssertIsOpen()
{
	AssertIsNotDisposed();
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
	AssertIsOpen();
	auto err = vkEndCommandBuffer(_vkCommandBuffer);
	AssertVulkanSuccess(err);
	_isOpen = false;
}

void VulkanCommandBuffer::EndRenderPass()
{
	AssertIsOpen();
	vkCmdEndRenderPass(_vkCommandBuffer);
}







 

void VulkanCommandBuffer::Delete() {
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
	AssertIsOpen();
	VkDeviceSize off = 0;
	vkCmdBindVertexBuffers(_vkCommandBuffer, 0, 1, &buff,&off);
	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::BindIndexBuffer(VkBuffer buff)
{
	AssertIsOpen();

	vkCmdBindIndexBuffer(_vkCommandBuffer, buff, 0, VK_INDEX_TYPE_UINT32);
	return *this;
}





VulkanCommandBuffer& VulkanCommandBuffer::CopyBuffers(VkBuffer src, VkBuffer dst, long size)
{
	AssertIsOpen();

	VkBufferCopy copyRegion = {};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = size;
	vkCmdCopyBuffer( _vkCommandBuffer, src,dst,1, &copyRegion);
	return *this;
}

#pragma region Image Commands
VulkanCommandBuffer& VulkanCommandBuffer::TransitionImageToCopyTarget( VulkanImage& image)
{
	AssertIsOpen();
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = image.GetCurrentImageLayout();
	barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED; //We are not exchanging queue on the image. so ignore
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image.GetHandle();
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;
	barrier.srcAccessMask = VK_ACCESS_NONE; //No read no writes the initial layous is assumed unusable
	barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT; //After the layout transition you can write into the resource not read from it
	



	vkCmdPipelineBarrier(
		this->GetHandle(),
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, //The stage before the barrier. That is the top of the pipeline before any processing takes place
		VK_PIPELINE_STAGE_TRANSFER_BIT,    //The first stage that should wait for the barrier.  This stage is the one where memory transfers and copy should happen
		0, //Global  device wide dependency
		0, nullptr, 
		0, nullptr,
		1,&barrier);

	image.SetCurrentLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	
	return *this;

}

VulkanCommandBuffer& VulkanCommandBuffer::TransitionImageToFinalLayout(VulkanImage& image)
{
	AssertIsOpen();
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = image.GetCurrentImageLayout();
	barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; //this will change when We need images for other than just shader textures.
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED; //We are not exchanging queue on the image. so ignore
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image.GetHandle();
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;
	barrier.srcAccessMask = image.GetCurrentAccessMask(); //No read no writes the initial layous is assumed unusable
	barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT; //After the layout transition you can write into the resource not read from it




	vkCmdPipelineBarrier(
		this->GetHandle(),
		VK_PIPELINE_STAGE_TRANSFER_BIT,//The stage before the barrier. That is the top of the pipeline before any processing takes place
		VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,  //The first stage that should wait for the barrier.  This stage is the one where memory transfers and copy should happen
		0, //Global  device wide dependency
		0, nullptr,
		0, nullptr,
		1, &barrier);

	image.SetCurrentLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	image.SetCurrentAccessMask(barrier.dstAccessMask);

	return *this;
}

VulkanCommandBuffer& VulkanCommandBuffer::CopyToImage(VulkanBuffer& buffer, VulkanImage& image)
{
	AssertIsOpen();
	eassert(image.GetSizeInBytes() >= buffer.GetSizeInBytes(), "Image too small to copy buffer into");
	eassert(image.GetCurrentImageLayout() == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, "Image layout must be optimal")
	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = image.GetExtent();
	
	vkCmdCopyBufferToImage(this->GetHandle(), buffer.GetHandle(), image.GetHandle(), image.GetCurrentImageLayout(), 1, &region);


	return *this;
}



#pragma endregion