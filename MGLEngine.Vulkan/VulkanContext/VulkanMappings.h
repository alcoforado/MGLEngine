#pragma once
#include <cstdint>
#include <vector>
enum FieldType;
enum VkFormat;
enum ShaderStage;
enum VkShaderStageFlagBits;
typedef uint32_t VkShaderStageFlags;
typedef uint32_t VkFlags;
class VulkanMappings {
public:
	static VkShaderStageFlags Map(ShaderStage stg);
	static VkFormat MapFormat(FieldType field);
};