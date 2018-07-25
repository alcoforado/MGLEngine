#pragma once
#include <vector>
#include "VulkanRenderPass.h"
#include "VulkanSwapChainFramebuffers.h"
#include <MGLEngine.Shared/Utils/opointer.h>
#include <MGLEngine.Shared/Utils/observable.h>
#include <glm/detail/type_vec4.hpp>
#include "VulkanCommandBuffer.h"
#include "VulkanInputLayout.h"
#include "MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetLayout.h"
class VulkanDescriptorSet;
class VulkanCommandPool;
class VulkanSwapChain;
class VertexShaderByteCode;
class FragmentShaderByteCode;
#include <vulkan/vulkan.h>
class VulkanPipeline
{
	const VulkanSwapChain *_swapChain;
	VkPipelineLayout _vkPipelineLayout;
	const VulkanLogicalDevice *_pLogicalDevice;
	bool _isLoaded;
	VkPipeline _vkPipeline;
	VkPipelineLayoutCreateInfo PipelineLayoutInfo;
	std::vector<VulkanDescriptorSetLayout*> _descriptorSetLayouts;
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
	VulkanRenderPass RenderPass;
	VkGraphicsPipelineCreateInfo pipelineInfo;
	std::vector<VkDynamicState>  DynamicStates;
	Listener<VulkanSwapChain*> onResize;
	VkViewport Viewport;
	VkPipelineViewportStateCreateInfo ViewportState;

	VkRect2D Scissor;
	OPointer<VulkanSwapChainFramebuffers> _pFramebuffers;

	VulkanPipeline(const VulkanSwapChain *pSwapChain,VertexShaderByteCode& vertexCode, FragmentShaderByteCode& fragment);
	VkPipeline GetHandle() const { return _vkPipeline; }

	void Load();
	const VulkanLogicalDevice& GetLogicalDevice() const { return *_pLogicalDevice; }
	const VulkanSwapChain& GetSwapChain() const { return *_swapChain; }
	bool  IsLoaded() const { return _isLoaded; }
	const VulkanSwapChainFramebuffers* GetVulkanSwapChainFramebuffers() const { assert(_isLoaded); return _pFramebuffers; }
	const VkPipelineLayout GetVulkanPipelineLayout() const { assert(_isLoaded); return _vkPipelineLayout; }
	void Dispose();

	
	void OnSwapChainReload(const VulkanSwapChain *pNewSwapChaing);
	

	//The Descriptor Sets binded to the pipeline
	void AddDescriptorSetLayout(VulkanDescriptorSetLayout *layout);
	std::vector<VulkanDescriptorSetLayout*> GetDescriptorSetLayouts() const { return _descriptorSetLayouts; }


	~VulkanPipeline();
};

