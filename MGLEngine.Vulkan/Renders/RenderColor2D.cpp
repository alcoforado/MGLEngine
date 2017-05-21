#include "RenderColor2D.h"
#include <vector>
#include "IRenderContext.h"
#include "../shaders/shaders_bytecode.h"

RenderColor2D::RenderColor2D(IRenderContext& renderContext)
{
	VertexShaderByteCode vertexByteCode(renderContext.GetLogicalDevice(),canvas2D_vert,sizeof(canvas2D_vert));
	FragmentShaderByteCode fragShaderCode(renderContext.GetLogicalDevice(), canvas2D_frag, sizeof(canvas2D_frag));

	_pPipeline = new VulkanPipeline(renderContext.GetSwapChain(), vertexByteCode, fragShaderCode);
	
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
	
	
	auto framebuffers = _pPipeline->GetVulkanSwapChainFramebuffers();
	glm::vec4 color(0, 0, 0, 1.0);
	for (int i=0;i<framebuffers->Size();i++)
	{
		auto framebuffer = framebuffers->GetFramebuffer(i);
		VulkanCommandBuffer* comm = new VulkanCommandBuffer(renderContext.GetCommandPool());
		comm->BeginRenderPass(framebuffer,glm::vec4(0,0,0,0));
		comm->BindPipeline(_pPipeline);
		comm->Draw(3, 1, 0, 0);
		comm->EndRenderPass();
		comm->End();
		_commands.push_back(comm);
	}
	

}

RenderColor2D::~RenderColor2D()
{
	_pPipeline.if_free();
	for(auto pc: _commands)
	{
		delete pc;
	}
}

const VulkanSemaphore& RenderColor2D::Draw(const VulkanSemaphore& wait)
{
	uint32_t index = _pPipeline->GetSwapChain().GetCurrentImageIndex();
	return _commands[index]->SubmitPipelineAsync(wait,VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
}
