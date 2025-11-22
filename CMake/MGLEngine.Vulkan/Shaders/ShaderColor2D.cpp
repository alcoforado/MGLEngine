#include "ShaderColor2D.h"
#include <vector>
#include "IVulkanRenderContext.h"
#include "../SPIR-V/headers/canvas2d_frag.h"
#include "../SPIR-V/headers/canvas2d_vert.h"
#include <MGLEngine.Vulkan/MemoryManager/VulkanBuffer.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>
#include "MGLEngine.Vulkan/RenderResources/VulkanDescriptorSetLayout.h"
#include <MGLEngine.Vulkan\DrawTree\VulkanResourceLoader.h>
ShaderColor2D::ShaderColor2D(IVulkanRenderContext* renderContext)
 :_vertexByteCode(*renderContext->GetLogicalDevice(), canvas2D_vert, sizeof(canvas2D_vert)),
  _fragShaderCode(*renderContext->GetLogicalDevice(), canvas2D_frag, sizeof(canvas2D_frag))
{
	_pGT = new UniformBufferSlot<glm::mat4>(renderContext->GetMemoryManager(), 0, 1, { VK_SHADER_STAGE_VERTEX_BIT }, MAPPED_MEMORY, ONCE_PER_FRAME);

	_pPipeline = new VulkanPipeline(renderContext->GetSwapChain(), _vertexByteCode, _fragShaderCode,{_pGT});

	_pPipeline->VertexInputInfo
		.CreateBinding<Color2D>()
		.AddField(0, &Color2D::Position)
		.AddField(1, &Color2D::Color);

	_pPipeline->Rasterizer.cullMode= VK_CULL_MODE_NONE;


	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = renderContext->GetSwapChain()->GetImageFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


	_pPipeline->RenderPass.AddColorDescription("color", colorAttachment);
	_pPipeline->RenderPass
		.AddGraphicSubpass("pass1")
		.RefColorAttachement("color", VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);


	_pPipeline->GetSlotManager()->RegisterDescriptorSetLayout("perFrame",{ _pGT });

	
	_pPipeline->Load();

	//Setting the ResourceLoaders
	//allocate descriptor sets
	auto ds =_pPipeline->GetSlotManager()->AllocateDescritorSets("perFrame", 3);
	this->GetRoot()->GetData().InternalEngineData().AddResourceLoaderPerFrame(*_pGT, ds);
	_treeParser = new VulkanDrawTreeParser<Color2D>(renderContext, _pPipeline, *this,"perFrame");



}




ShaderColor2D::~ShaderColor2D()
{
	
}





void  ShaderColor2D::Draw(IDrawContext *pDrawContext)
{
	_treeParser->ExecuteTree(pDrawContext);
	
}

void ShaderColor2D::SetGlobalTransform(glm::mat3 m)
{
	_pGT->SetData(m);
	
}
