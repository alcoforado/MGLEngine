#pragma once	
#include <MGLEngine.Shared/Interfaces/IDrawContext.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Container/MGLContainer.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBuffer.h>

class VulkanDrawContext : public IDrawContext
{
	const ShapeElement& _drawContext;
	std::string _shaderId;
	VulkanCommandBuffer& _commandBuffer;
protected:
	void _PushConstant(std::string varName, void* pData, size_t typeIndex, size_t sizeofT) override;
	

public:
	VulkanDrawContext(VulkanCommandBuffer &cmd,std::string shaderId,const ShapeElement& gc)
		:_drawContext(gc), _commandBuffer(cmd),_shaderId(shaderId)
	{
	}
	void DrawIndexed() override {
		_commandBuffer.DrawIndexed(
			static_cast<uint32_t>(_drawContext.allocatedIndices), 
			static_cast<uint32_t>(_drawContext.startIndice), 
			static_cast<uint32_t>(_drawContext.startVertex));
	}
};