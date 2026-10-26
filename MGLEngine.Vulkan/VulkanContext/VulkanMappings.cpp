#include "VulkanMappings.h"
#include <MGLEngine.Vulkan/VulkanGL.h>
#include <MGLEngine.Shared//Shaders/ShaderConfiguration.h>

VkShaderStageFlags VulkanMappings::Map(ShaderStage stage)
{
	switch (stage)
	{
	case ShaderStage::FRAGMENT_STAGE:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
	case ShaderStage::VERTEX_STAGE:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
	case ShaderStage::VERTEX_FRAGMENT_STAGE:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT | VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
	default:
		throw_error("Cannot Map Shader Stage");
		
	}
	
}