#pragma once
#include "VulkanCommandPool.h"
#include <glm/detail/type_vec4.hpp>
#include "VulkanSemaphore.h"
#include "VulkanBuffer.h"

class VulkanPipeline;
class VulkanFramebuffer;
class VulkanCommandBuffer;

class VulkanCommandBufferOptions
{
	int _bufferUsageFlag;
public:
	friend class VulkanCommandBuffer;
	VulkanCommandBufferOptions()
	{
		_bufferUsageFlag = 0;
	}

	VulkanCommandBufferOptions OneTimeSubmit()
	{
		_bufferUsageFlag |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		return *this;
	}
	VulkanCommandBufferOptions RenderPassContinue()
	{
		_bufferUsageFlag |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
		return *this;

	}
	VulkanCommandBufferOptions SimultaneousUse()
	{
		_bufferUsageFlag |= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		return *this;
     }

};

class VulkanCommandBuffer
{
	friend class VulkanCommandPool;
	const VulkanCommandPool* _pPool;
	VkCommandBuffer _vkCommandBuffer;
	const VulkanPipeline *_pipeline;
	VkSubmitInfo *_pSubmitInfoCache;
	
	bool _isOpen;
	void AssertIsOpen();
	VulkanCommandBuffer(const VulkanCommandPool* pool, VulkanCommandBufferOptions* options);

public:




	VulkanCommandBuffer& BeginRenderPass(VulkanFramebuffer framebuffer, glm::vec4 color);

	VulkanCommandBuffer& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

	VulkanCommandBuffer& BindPipeline(const VulkanPipeline* pipeline);

	VulkanCommandBuffer& BindVertexBuffer(VkBuffer buff);
	
	VulkanCommandBuffer& CopyBuffers(VkBuffer src, VkBuffer dst, long size);
	
	void End();
	void EndRenderPass();
	
	VulkanSemaphore*  SubmitPipelineAsync(VulkanSemaphore* wait, VkPipelineStageFlagBits pipelineStage);

	~VulkanCommandBuffer();
	VkCommandBuffer GetHandle() const;
};

