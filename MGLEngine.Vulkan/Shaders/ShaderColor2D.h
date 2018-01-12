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
#include "../RenderPipeline/VulkanBuffer.h"
#include "../RenderPipeline/VulkanDrawTreeParser.h"
#include "MGLEngine.Vulkan/RenderResources/ConstantBuffer.h"
class IVulkanRenderContext;



class ShaderColor2D : public DrawTree<Color2D>
{
	OPointer<VulkanDrawTreeParser<Color2D>> _treeParser;
	OPointer<VulkanPipeline> _pPipeline;
	VertexShaderByteCode _vertexByteCode; 
	FragmentShaderByteCode _fragShaderCode;  
	std::vector<VulkanCommandBuffer*> _commands;
	OPointer<ConstantBuffer<glm::mat3>> _pGT;

	void CreateCommands(IVulkanRenderContext& renderContext);
	public:
	explicit ShaderColor2D(IVulkanRenderContext& renderContext);
	~ShaderColor2D();
	void OnSwapChange();
	VulkanSemaphore* Draw(IDrawContext *pDrawContext);
	void SetGlobalTransform(glm::mat3 mat3);

};

