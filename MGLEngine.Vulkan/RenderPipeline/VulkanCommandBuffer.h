#pragma once
#include "VulkanCommandPool.h"
#include <glm/detail/type_vec4.hpp>
#include "VulkanSemaphore.h"
#include "VulkanBuffer.h"

class VulkanPipeline;
class VulkanFramebuffer;

class VulkanCommandBuffer
{
	friend class VulkanCommandPool;
	const VulkanCommandPool* _pPool;
	VkCommandBuffer _vkCommandBuffer;
	const VulkanPipeline *_pipeline;
	VkSubmitInfo *_pSubmitInfoCache;
	
	bool _isOpen;
	void AssertIsOpen();
	VulkanSemaphore _lock;
	VulkanCommandBuffer(const VulkanCommandPool* pool);

public:




	VulkanCommandBuffer& BeginRenderPass(VulkanFramebuffer framebuffer, glm::vec4 color);

	VulkanCommandBuffer& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

	VulkanCommandBuffer& BindPipeline(const VulkanPipeline* pipeline);

	VulkanCommandBuffer& BindVertexBuffer(VkBuffer buff);
	
	void End();
	void EndRenderPass();
	
	VulkanSemaphore*  SubmitPipelineAsync(VulkanSemaphore* wait, VkPipelineStageFlagBits pipelineStage);

	~VulkanCommandBuffer();
};

