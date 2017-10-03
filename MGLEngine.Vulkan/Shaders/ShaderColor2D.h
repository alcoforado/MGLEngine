#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include <memory>
#include <MGLEngine.Shared/Utils/opointer.h>
#include "../RenderPipeline/VulkanCommandBuffer.h"
#include <glm/glm.hpp>
#include <MGLEngine.Shared/Utils/DrawTree/DrawTree.h>
#include <MGLEngine.Shared/VerticeData/Color2D.h>
#include "../RenderPipeline/VulkanStagingBuffer.h"
#include "../RenderPipeline/VulkanDrawTreeParser.h"
class IVulkanRenderContext;



class ShaderColor2D : public DrawTree<Color2D>
{
	OPointer<VulkanDrawTreeParser<Color2D>> _treeParser;
	OPointer<VulkanPipeline> _pPipeline;
	VertexShaderByteCode _vertexByteCode; 
	FragmentShaderByteCode _fragShaderCode;  
	std::vector<VulkanCommandBuffer*> _commands;


	void CreateCommands(IVulkanRenderContext& renderContext);
	public:
	explicit ShaderColor2D(IVulkanRenderContext& renderContext);
	~ShaderColor2D();
	void OnSwapChange();
	VulkanSemaphore* Draw(IDrawContext *pDrawContext);
};

