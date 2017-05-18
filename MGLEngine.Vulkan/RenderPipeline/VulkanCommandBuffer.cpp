#include "VulkanCommandBuffer.h"
#include "VulkanCommandPool.h"
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "../RenderPipeline/VulkanRenderPass.h"
#include <glm/vec4.hpp>

class VulkanRenderPass;

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanCommandPool &pool)
:_pool(pool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _pool.GetHandle();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	vkAllocateCommandBuffers(pool.GetLogicalDevice().GetHandle(), &allocInfo, &_vkCommandBuffer);
}

VulkanCommandBuffer& VulkanCommandBuffer::BeginRenderPass(const VulkanRenderPass *renderPass,VkFramebuffer framebuffer,glm::vec4 color )
{
	VkClearValue cl = { color.x,color.y,color.z,color.w };
	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass->GetHandle();
	renderPassInfo.framebuffer = framebuffer;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPass->GetSwapChain().

	return *this;
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
}
