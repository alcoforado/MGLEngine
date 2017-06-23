#include "ShaderColor2D.h"
#include <vector>
#include "IRenderContext.h"
#include "../SPIR-V/shaders_bytecode.h"
#include "../RenderPipeline/VulkanStagingBuffer.h"

ShaderColor2D::ShaderColor2D(IRenderContext& renderContext)
{
	this->Resize(renderContext);
}




ShaderColor2D::~ShaderColor2D()
{
	
}

void ShaderColor2D::OnSwapChange()
{
	_pPipeline.if_free();
	for (auto pc : _commands)
	{
		delete pc;
	}
	_commands.clear();
}

void ShaderColor2D::Resize(IRenderContext & renderContext)
{
	_pPipeline.if_free();
	_treeParser.if_free();
	
	VertexShaderByteCode vertexByteCode(renderContext.GetLogicalDevice(), canvas2D_vert, sizeof(canvas2D_vert));
	FragmentShaderByteCode fragShaderCode(renderContext.GetLogicalDevice(), canvas2D_frag, sizeof(canvas2D_frag));

	_pPipeline = new VulkanPipeline(renderContext.GetSwapChain(), vertexByteCode, fragShaderCode);

	_pPipeline->VertexInputInfo
		.CreateBinding<Color2D>()
		.AddField(0, &Color2D::Position)
		.AddField(1, &Color2D::Color);


	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = renderContext.GetSwapChain().GetImageFormat();
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

	_pPipeline->Load();


	_treeParser = new VulkanDrawTreeParser<Color2D>(renderContext, *_pPipeline, *this);

}




const VulkanSemaphore& ShaderColor2D::Draw(const VulkanSemaphore& wait)
{
	_treeParser->ExecuteTree();
	uint32_t index = _pPipeline->GetSwapChain().GetCurrentImageIndex();
	return _treeParser->GetCommandForFrame(index)->SubmitPipelineAsync(wait,VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
}
