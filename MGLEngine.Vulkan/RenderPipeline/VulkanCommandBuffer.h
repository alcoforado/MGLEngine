#pragma once
#include "VulkanCommandPool.h"
#include <glm/detail/type_vec4.hpp>
#include "VulkanSemaphore.h"

class VulkanPipeline;
class VulkanFramebuffer;

class VulkanCommandBuffer
{
	const VulkanCommandPool& _pool;
	VkCommandBuffer _vkCommandBuffer;
	const VulkanPipeline *_pipeline;
	VkSubmitInfo *_pSubmitInfoCache;
	
	bool _isOpen;
	void AssertIsOpen();
	VulkanSemaphore _lock;

public:
	VulkanCommandBuffer();
	VulkanCommandBuffer(const VulkanCommandPool& pool);

	VulkanCommandBuffer & BeginRenderPass(const VulkanFramebuffer & framebuffer, glm::vec4 color);

	VulkanCommandBuffer & Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

	VulkanCommandBuffer & BindPipeline(const VulkanPipeline& pipeline);

	void End();
	const VulkanSemaphore&  Submit(VulkanSemaphore& wait, VkPipelineStageFlagBits pipelineStage);

	~VulkanCommandBuffer();
};

