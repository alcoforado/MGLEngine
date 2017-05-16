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
	


}

RenderColor2D::~RenderColor2D()
{

}
