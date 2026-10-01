#pragma once	
#include <MGLEngine.Shared/Interfaces/IDrawContext.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>

class VulkanDrawContext : public IDrawContext
{
	const ShapeElement& _drawContext;
	VulkanCommandBuffer& _commandBuffer;
public:
	VulkanDrawContext(VulkanCommandBuffer &cmd,const ShapeElement& gc)
		:_drawContext(gc), _commandBuffer(cmd)
	{
	}
	void DrawIndexed() override {
		_commandBuffer.DrawIndexed(
			static_cast<uint32_t>(_drawContext.allocatedIndices), 
			static_cast<uint32_t>(_drawContext.startIndice), 
			static_cast<uint32_t>(_drawContext.startVertex));
	}
};