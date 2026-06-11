#pragma once
#include "VulkanCommandPool.h"
#include <glm/vec4.hpp>
#include "VulkanSemaphore.h"
#include <string>
class VulkanDescriptorSet;
class VulkanPipeline;
class VulkanCommandBuffer;


class VulkanCommandBuffer
{
	friend class VulkanCommandPool;
public:
	

private:
	VulkanCommandPool* _pPool;
	VkCommandBuffer _vkCommandBuffer;
	
	bool _isOpen=false;
	void AssertIsOpen();
	void AssertIsNotDisposed() const;

public:
	VulkanCommandBuffer(VulkanCommandPool* pool);
	VulkanCommandBuffer& Reset();
	VulkanCommandBuffer& Begin(bool asyncQueues=false, bool oneSubmissionPerReset=false);
	VulkanCommandBuffer& BeginRenderPass(VkRenderPass renderPass, VkFramebuffer framebuffer, VkExtent2D extent, glm::vec4 color);
	VulkanCommandBuffer& SetViewportAndScissor(VkExtent2D extent);

	VulkanCommandBuffer& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
	VulkanCommandBuffer& DrawIndexed(uint32_t indexCount, uint32_t firstIndex = 0, uint32_t vertexOffset = 0);


	VulkanCommandBuffer& BindGraphicsPipeline( VkPipeline pipeline);

	VulkanCommandBuffer& BindDescriptorSet(VulkanPipeline * pipeline, std::string layoutNumber, int dsNumber);
	VulkanCommandBuffer& BindDescriptorSet(VulkanPipeline* pipeline, VulkanDescriptorSet* ds);


	VulkanCommandBuffer& BindVertexBuffer(VkBuffer buff);
	VulkanCommandBuffer& BindIndexBuffer(VkBuffer buff);

	VulkanCommandBuffer& CopyBuffers(VkBuffer src, VkBuffer dst, long size);
	
	void End();
	void EndRenderPass();
	
	VulkanSemaphore*  SubmitPipelineAsync(VulkanSemaphore* wait, VkPipelineStageFlagBits pipelineStage);


	void Dispose();
	~VulkanCommandBuffer();
	VkCommandBuffer GetHandle() const;

};

