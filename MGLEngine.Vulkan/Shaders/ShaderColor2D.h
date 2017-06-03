#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include <memory>
#include <Utils/opointer.h>
#include "../RenderPipeline/VulkanCommandBuffer.h"
#include <glm/glm.hpp>
#include "Utils/DrawTree/DrawTree.h"
class IRenderContext;

struct Color2D
{
	glm::vec2 Position;
	glm::vec3 Color;
};

class ShaderColor2D :DrawTree<Color2D>
{
	OPointer<VulkanPipeline> _pPipeline;
	std::vector<VulkanCommandBuffer*> _commands;
	
	public:
	explicit ShaderColor2D(IRenderContext& renderContext);
	~ShaderColor2D();
	void OnSwapChange();
	const VulkanSemaphore& Draw(const VulkanSemaphore& wait);
};

