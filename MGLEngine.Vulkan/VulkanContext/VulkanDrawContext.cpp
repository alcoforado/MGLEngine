#include "VulkanDrawContext.h"
#include <MGLEngine.Shared/Resources/ResourceManager.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanGL.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMappings.h>
void VulkanDrawContext::_PushConstant(std::string varName, void* pData, size_t typeIndex, size_t sizeofT) 
{
	auto& pushConstant = _shader.GetConfiguration().pushConstant;

	eassert(_shader.GetConfiguration().pushConstant.Validate(varName, typeIndex, sizeofT), std::format("Wrong assignment for Push Constant {} ", varName));
	_commandBuffer.PushConstant(
		_vulkanShaderData.pipeline.layout, 
		VulkanMappings::Map(pushConstant.stage), 
		pData, 
		sizeofT);
}

