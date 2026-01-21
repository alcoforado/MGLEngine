#pragma once
#include "VulkanCommandPool.h"
#include <glm/vec4.hpp>
#include "VulkanSemaphore.h"
#include <string>
class VulkanDescriptorSet;
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
public:
	struct Statistics
	{
		int TransferCommands = 0;
		int ActionCommands = 0;
		int Total() { return TransferCommands + ActionCommands; }
	};

private:
	const VulkanCommandPool* _pPool;
	VkCommandBuffer _vkCommandBuffer;
	VkSubmitInfo *_pSubmitInfoCache;
	VulkanPipeline *_vulkanPipeline;
	
	bool _isOpen;
	void AssertIsOpen();
	Statistics _statistics;

public:
	VulkanCommandBuffer(const VulkanCommandPool* pool, VulkanCommandBufferOptions* options);
	VulkanCommandBuffer& BeginRenderPass(VulkanFramebuffer framebuffer, glm::vec4 color);

	VulkanCommandBuffer& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

	VulkanCommandBuffer& BindPipeline(const VulkanPipeline* pipeline);

	VulkanCommandBuffer& BindDescriptorSet(VulkanPipeline * pipeline, std::string layoutNumber, int dsNumber);
	VulkanCommandBuffer& BindDescriptorSet(VulkanPipeline* pipeline, VulkanDescriptorSet* ds);


	VulkanCommandBuffer& BindVertexBuffer(VkBuffer buff);
	
	VulkanCommandBuffer& CopyBuffers(VkBuffer src, VkBuffer dst, long size);
	
	void End();
	void EndRenderPass();
	
	VulkanSemaphore*  SubmitPipelineAsync(VulkanSemaphore* wait, VkPipelineStageFlagBits pipelineStage);

	~VulkanCommandBuffer();
	VkCommandBuffer GetHandle() const;

	Statistics GetStatistics() const;
};

