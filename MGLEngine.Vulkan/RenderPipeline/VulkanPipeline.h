#pragma once
#include <vector>
#include "VulkanRenderPass.h"
#include "VulkanSwapChainFramebuffers.h"
#include "Utils/opointer.h"
#include "Utils/observable.h"
#include <glm/detail/type_vec4.hpp>
#include "VulkanCommandBuffer.h"
#include "VulkanInputLayout.h"
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
	VulkanInputLayout VertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	VkPipelineRasterizationStateCreateInfo Rasterizer;
	VkPipelineMultisampleStateCreateInfo Multisampling;
	VkPipelineColorBlendAttachmentState ColorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo ColorBlending;
	VkPipelineLayoutCreateInfo PipelineLayoutInfo;
	VulkanRenderPass RenderPass;
	VkGraphicsPipelineCreateInfo pipelineInfo;
	std::vector<VkDynamicState>  DynamicStates;
	Listener<VulkanSwapChain*> onResize;
	VkViewport Viewport;
	VkPipelineViewportStateCreateInfo ViewportState;

	VkRect2D Scissor;
	OPointer<VulkanSwapChainFramebuffers> _pFramebuffers;

	VulkanPipeline(const VulkanSwapChain &swapChain,VertexShaderByteCode& vertexCode, FragmentShaderByteCode& fragment);
	VkPipeline GetHandle() const { return _vkPipeline; }

	void Load();
	const VulkanSwapChain& GetSwapChain() const { return _swapChain; }
	bool  IsLoaded() const { return _isLoaded; }
	const VulkanSwapChainFramebuffers* GetVulkanSwapChainFramebuffers() const { assert(_isLoaded); return _pFramebuffers; }
	void Dispose();

	
	~VulkanPipeline();
};

