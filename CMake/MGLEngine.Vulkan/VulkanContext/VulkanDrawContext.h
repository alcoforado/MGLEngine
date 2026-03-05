#pragma once	
#include <MGLEngine.Shared/Interfaces/IDrawContext.h>
#include <MGLEngine.Vulkan/VulkanApp/ShaderContext.h>

class VulkanDrawContext : public IDrawContext
{
	const DrawElementContext& _drawContext;
	VulkanCommandBuffer& _commandBuffer;
public:
	VulkanDrawContext(VulkanCommandBuffer &cmd,const DrawElementContext& gc)
		:_drawContext(gc), _commandBuffer(cmd)
	{
	}
	void DrawIndexed() override {
		_commandBuffer.DrawIndexed(_drawContext.allocatedIndices,  _drawContext.startIndice, _drawContext.startVertex);
	}
};