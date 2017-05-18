#include "VulkanPipeline.h"
#include "VertexShaderByteCode.h"
#include "FragmentShaderByteCode.h"
#include "../VulkanContext/VulkanSwapChain.h"
#include "../VulkanUtils.h"
#include <cassert>
#include "Utils/Exception.h"


VulkanPipeline::VulkanPipeline(const VulkanSwapChain &swapChain, VertexShaderByteCode& vertexCode,FragmentShaderByteCode& fragment)
	:_swapChain(swapChain),
	RenderPass(swapChain.GetLogicalDevice())
{
	_isLoaded = false;
	pipelineInfo.sType= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	



	VertShaderStageInfo = {};
	VertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	VertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	VertShaderStageInfo.module = vertexCode.GetHandle();
	VertShaderStageInfo.pName = "main";

	FragShaderStageInfo = {};
	FragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	FragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	FragShaderStageInfo.module = fragment.GetHandle();
	FragShaderStageInfo.pName = "main";
	
	ShaderStages.push_back(VertShaderStageInfo);
	ShaderStages.push_back(FragShaderStageInfo);


	VertexInputInfo = {};
	VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputInfo.vertexBindingDescriptionCount = 0;
	VertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
	VertexInputInfo.vertexAttributeDescriptionCount = 0;
	VertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

	InputAssembly = {};
	InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssembly.primitiveRestartEnable = VK_FALSE;

	//Set Viewport
	 
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width =static_cast<float>(swapChain.GetExtent().width);
	Viewport.height = static_cast<float>(swapChain.GetExtent().height);
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;
	
	Scissor = {};
	Scissor.offset = { 0, 0 };
	Scissor.extent = swapChain.GetExtent();
	


	Rasterizer = {};
	Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	Rasterizer.depthClampEnable = VK_FALSE;
	Rasterizer.rasterizerDiscardEnable = VK_FALSE;
	Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	Rasterizer.lineWidth = 1.0f;
	Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	Rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	Rasterizer.depthBiasEnable = VK_FALSE;
	Rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	Rasterizer.depthBiasClamp = 0.0f; // Optional
	Rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	Multisampling = {};
	Multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	Multisampling.sampleShadingEnable = VK_FALSE;
	Multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	Multisampling.minSampleShading = 1.0f; // Optional
	Multisampling.pSampleMask = nullptr; /// Optional
	Multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	Multisampling.alphaToOneEnable = VK_FALSE; // Optional

	ColorBlendAttachment = {};
	ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColorBlendAttachment.blendEnable = VK_FALSE;
	ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

	ColorBlending = {};
	ColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlending.logicOpEnable = VK_FALSE;
	ColorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	ColorBlending.attachmentCount = 1;
	ColorBlending.pAttachments = &ColorBlendAttachment;
	ColorBlending.blendConstants[0] = 0.0f; // Optional
	ColorBlending.blendConstants[1] = 0.0f; // Optional
	ColorBlending.blendConstants[2] = 0.0f; // Optional
	ColorBlending.blendConstants[3] = 0.0f; // Optional

	
	PipelineLayoutInfo = {};
	PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	PipelineLayoutInfo.setLayoutCount = 0; // Optional
	PipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	PipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	PipelineLayoutInfo.pPushConstantRanges = 0; // Optional




	

}

void VulkanPipeline::Load()
{
	if (_isLoaded)
	{
		throw new Exception("Error, pipeline is already loaded");
	}

	pipelineInfo.stageCount = static_cast<uint32_t>(ShaderStages.size());
	pipelineInfo.pStages = ShaderStages.data();
	pipelineInfo.pVertexInputState = &VertexInputInfo;
	pipelineInfo.pInputAssemblyState = &InputAssembly;
	
	
	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &Viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &Scissor;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &Rasterizer;
	pipelineInfo.pMultisampleState = &Multisampling;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &ColorBlending;
	pipelineInfo.pDynamicState = nullptr;


	auto err = vkCreatePipelineLayout(_swapChain.GetLogicalDevice().GetHandle(), &PipelineLayoutInfo, nullptr, &_vkPipelineLayout);
	AssertVulkanSuccess(err);

	pipelineInfo.layout = _vkPipelineLayout;
	
	auto renderHandle = RenderPass.Load();
	pipelineInfo.renderPass = renderHandle;
	pipelineInfo.subpass = 0;
	
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	err = vkCreateGraphicsPipelines(_swapChain.GetLogicalDevice().GetHandle(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_vkPipeline);
	AssertVulkanSuccess(err);


	_pFramebuffer = new VulkanSwapChainFramebuffers(RenderPass,_swapChain);
}


VulkanPipeline::~VulkanPipeline()
{
	if (_isLoaded)
	{

		vkDestroyPipeline(_swapChain.GetLogicalDevice().GetHandle(), _vkPipeline, nullptr);
		vkDestroyPipelineLayout(_swapChain.GetLogicalDevice().GetHandle(), _vkPipelineLayout, nullptr);
		
	}
}

