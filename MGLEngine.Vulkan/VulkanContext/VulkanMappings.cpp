#include "VulkanMappings.h"
#include <MGLEngine.Vulkan/VulkanGL.h>
#include <MGLEngine.Shared//Shaders/ShaderConfiguration.h>
#include <MGLEngine.Shared/Shaders/FieldType.h>


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

VkFormat VulkanMappings::MapFormat(FieldType field)
{
	static std::vector<VkFormat> map = {
		 VK_FORMAT_R32_UINT,			// TYPE_UINT
		VK_FORMAT_R32_SFLOAT,			//TYPE_FLOAT
		VK_FORMAT_R32G32_SFLOAT,		//TYPE_VEC_FLOAT_2
		VK_FORMAT_R32G32B32_SFLOAT,		//TYPE_VEC_FLOAT_3
		VK_FORMAT_R32G32B32A32_SFLOAT	//TYPE_VEC_FLOAT_4;
	};
	eassert(field >= 0 && field < 5, "Field Type conversion not supported");
	return map[field];


	
}