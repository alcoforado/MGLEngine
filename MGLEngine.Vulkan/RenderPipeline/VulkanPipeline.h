#pragma once
#include <vector>
#include "VulkanRenderPass.h"
#include "VulkanSwapChainFramebuffers.h"
#include "Utils/opointer.h"
#include <glm/detail/type_vec4.hpp>
#include "VulkanCommandBuffer.h"
class VulkanCommandPool;
class VulkanSwapChain;
class VertexShaderByteCode;
class FragmentShaderByteCode;
#include <vulkan/vulkan.h>
class VulkanPipeline
{
	const VulkanSwapChain &_swapChain;
	VkPipelineLayout _vkPipelineLayout;
	bool _isLoaded;
	VkPipeline _vkPipeline;
public:
	VkPipelineShaderStageCreateInfo FragShaderStageInfo;
	VkPipelineShaderStageCreateInfo VertShaderStageInfo;
	std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;
	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	VkPipelineRasterizationStateCreateInfo Rasterizer;
	VkPipelineMultisampleStateCreateInfo Multisampling;
	VkPipelineColorBlendAttachmentState ColorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo ColorBlending;
	VkPipelineLayoutCreateInfo PipelineLayoutInfo;
	VulkanRenderPass RenderPass;
	VkGraphicsPipelineCreateInfo pipelineInfo;
	std::vector<VkDynamicState>  DynamicStates;

	VkViewport Viewport;
	VkRect2D Scissor;
	OPointer<VulkanSwapChainFramebuffers> _pFramebuffer;

	VulkanPipeline(const VulkanSwapChain &swapChain,VertexShaderByteCode& vertexCode, FragmentShaderByteCode& fragment);
	VkPipeline GetHandle() const { return _vkPipeline; }

	void Load();
	const VulkanSwapChain& GetSwapChain() const { return _swapChain; };
	const VulkanSwapChainFramebuffers* GetVulkanSwapChainFramebuffers() const { assert(_isLoaded); return _pFramebuffer; }
	

	
	~VulkanPipeline();
};

