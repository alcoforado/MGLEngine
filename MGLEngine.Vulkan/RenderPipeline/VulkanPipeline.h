#pragma once
#include <vector>
#include "VulkanRenderPass.h"
class VulkanSwapChain;
class VertexShaderByteCode;
class FragmentShaderByteCode;
#include <vulkan/vulkan.h>
class VulkanPipeline
{
	const VulkanSwapChain &_swapChain;
	VkPipelineLayout _vkPipelineLayout;
	bool _isLoaded;
	
public:
	VkPipelineShaderStageCreateInfo FragShaderStageInfo;
	VkPipelineShaderStageCreateInfo VertShaderStageInfo;
	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	VkPipelineRasterizationStateCreateInfo Rasterizer;
	VkPipelineMultisampleStateCreateInfo Multisampling;
	VkPipelineColorBlendAttachmentState ColorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo ColorBlending;
	VkPipelineLayoutCreateInfo PipelineLayoutInfo;
	VulkanRenderPass RenderPass;

	std::vector<VkDynamicState>  DynamicStates;

	VulkanPipeline(const VulkanSwapChain &swapChain,VertexShaderByteCode& vertexCode, FragmentShaderByteCode& fragment);

	void Load();
	
	~VulkanPipeline();
};

