#pragma once
#include <cstdint>
enum ShaderStage;
enum VkShaderStageFlagBits;
typedef uint32_t VkShaderStageFlags;
typedef uint32_t VkFlags;
class VulkanMappings {
public:
	static VkShaderStageFlags Map(ShaderStage stg);

};