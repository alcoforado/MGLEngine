#pragma once
#include <vector>
class VulkanSwapChain;
class VertexShaderByteCode;
class FragmentShaderByteCode;
#include <vulkan/vulkan.h>
class VulkanPipeline
{
	VkPipelineLayout _vkPipelineLayout;
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
	std::vector<VkDynamicState>  DynamicStates;

	VulkanPipeline(const VulkanSwapChain &swapChain,VertexShaderByteCode& vertexCode, FragmentShaderByteCode& fragment);
	
	~VulkanPipeline();
};

