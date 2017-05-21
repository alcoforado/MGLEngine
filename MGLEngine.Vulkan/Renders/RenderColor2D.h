#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include <memory>
#include <Utils/opointer.h>
#include "../RenderPipeline/VulkanCommandBuffer.h"
class IRenderContext;

class RenderColor2D
{
	OPointer<VulkanPipeline> _pPipeline;
	std::vector<VulkanCommandBuffer*> _commands;
	
	public:
	explicit RenderColor2D(IRenderContext& renderContext);
	~RenderColor2D();
	void OnSwapChange();
	const VulkanSemaphore& Draw(const VulkanSemaphore& wait);
};

