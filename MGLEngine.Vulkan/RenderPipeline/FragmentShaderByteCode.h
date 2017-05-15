#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
enum ShaderByteCodeType {VERTEX_SHADER,FRAGMENT_SHADER};
class FragmentShaderByteCode
{
	const VulkanLogicalDevice& _device;
	VkShaderModule _vkModule;
public:
	//FragmentShaderByteCode(std::vector<uint32_t>& bytecode);
	FragmentShaderByteCode(const VulkanLogicalDevice &device, uint32_t* p, int size);
	~FragmentShaderByteCode();
	VkShaderModule GetHandle() const { return _vkModule; }
};

