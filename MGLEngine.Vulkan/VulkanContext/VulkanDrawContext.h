#pragma once	
#include <MGLEngine.Shared/Interfaces/IDrawContext.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Container/MGLContainer.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBuffer.h>
struct VulkanShaderData;
class VulkanDrawContext : public IDrawContext
{
	const ShapeElement& _drawContext;
	ShaderContext& _shader;
	VulkanCommandBuffer& _commandBuffer;
	VulkanShaderData& _vulkanShaderData;
protected:
	void _PushConstant(std::string varName, void* pData, size_t typeIndex, size_t sizeofT) override;
	

public:
	VulkanDrawContext(VulkanShaderData& shaderData,VulkanCommandBuffer &cmd,ShaderContext &shader,const ShapeElement& gc)
		:_vulkanShaderData(shaderData),_drawContext(gc), _commandBuffer(cmd),_shader(shader)
	{
	}
	void DrawIndexed() override {
		_commandBuffer.DrawIndexed(
			static_cast<uint32_t>(_drawContext.allocatedIndices), 
			static_cast<uint32_t>(_drawContext.startIndice), 
			static_cast<uint32_t>(_drawContext.startVertex));
	}
};