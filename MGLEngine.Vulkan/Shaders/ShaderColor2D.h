#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include <memory>
#include <Utils/opointer.h>
#include "../RenderPipeline/VulkanCommandBuffer.h"
#include <glm/glm.hpp>
#include "Utils/DrawTree/DrawTree.h"
#include "../RenderPipeline/VulkanStagingBuffer.h"
#include "../RenderPipeline/VulkanDrawTreeParser.h"
class IRenderContext;

struct Color2D
{
	glm::vec2 Position;
	glm::vec3 Color;
};

class ShaderColor2D : public DrawTree<Color2D>
{
	OPointer<VulkanDrawTreeParser<Color2D>> _treeParser;
	OPointer<VulkanPipeline> _pPipeline;
	std::vector<VulkanCommandBuffer*> _commands;
	void CreateCommands(IRenderContext& renderContext);
	public:
	explicit ShaderColor2D(IRenderContext& renderContext);
	~ShaderColor2D();
	void OnSwapChange();
	VulkanSemaphore Draw(IDrawContext *pDrawContext);
};

