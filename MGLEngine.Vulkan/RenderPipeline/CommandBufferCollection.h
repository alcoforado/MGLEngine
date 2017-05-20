#pragma once
#include "VulkanCommandPool.h"
#include <glm/detail/type_vec4.hpp>
#include "VulkanCommandBuffer.h"
#include <vector>
#include "VulkanSwapChainFramebuffers.h"

class VulkanPipeline;

class CommandBufferCollection
{
	const VulkanSwapChainFramebuffers& _framebuffers;
	std::vector<VulkanCommandBuffer> _commands;
public:
	CommandBufferCollection(const VulkanCommandPool *pool,const VulkanPipeline *pipeline,glm::vec4 color);
	~CommandBufferCollection();
};

