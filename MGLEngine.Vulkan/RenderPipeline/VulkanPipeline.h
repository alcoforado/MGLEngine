#pragma once
#include <vector>
#include "VulkanRenderPass.h"
#include "VulkanFramebuffer.h"
#include "Utils/opointer.h"
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
	OPointer<VulkanFramebuffer> _pFramebuffer;

	VulkanPipeline(const VulkanSwapChain &swapChain,VertexShaderByteCode& vertexCode, FragmentShaderByteCode& fragment);

	void Load();
	
	~VulkanPipeline();
};

