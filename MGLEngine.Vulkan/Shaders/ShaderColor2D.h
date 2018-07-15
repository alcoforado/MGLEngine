#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include <memory>
#include <MGLEngine.Shared/Utils/opointer.h>
#include "../RenderPipeline/VulkanCommandBuffer.h"
#include <glm/glm.hpp>
#include <MGLEngine.Shared/DrawTree/DrawTree.h>
#include <MGLEngine.Shared/VerticeData/Color2D.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanBuffer.h>

#include "../RenderPipeline/VulkanDrawTreeParser.h"
#include "MGLEngine.Vulkan/RenderResources/UniformBufferBinding.h"
#include "IVulkanShader.h"
class IVulkanRenderContext;



class ShaderColor2D : public DrawTree<Color2D>, public IVulkanShader
{
	OPointer<VulkanDrawTreeParser<Color2D>> _treeParser;
	OPointer<VulkanPipeline> _pPipeline;
	VertexShaderByteCode _vertexByteCode; 
	FragmentShaderByteCode _fragShaderCode;  
	std::vector<VulkanCommandBuffer*> _commands;
	OPointer<UniformBufferBinding<glm::mat3>> _pGT;

	public:
	explicit ShaderColor2D(IVulkanRenderContext& renderContext);
	~ShaderColor2D();
	void OnSwapChange();
	virtual void Draw(IDrawContext *pDrawContext);
	void SetGlobalTransform(glm::mat3 mat3);

};

