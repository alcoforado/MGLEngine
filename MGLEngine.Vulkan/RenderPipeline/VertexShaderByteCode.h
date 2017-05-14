#pragma once
#include <cstdint>
#include <vulkan/vulkan.h>

class VulkanLogicalDevice;

class VertexShaderByteCode
{
	VkShaderModule _vkModule;
public:
	VertexShaderByteCode(const VulkanLogicalDevice &device, uint32_t* p, int size);
	~VertexShaderByteCode();
	VkShaderModule GetHandle() const {
		return _vkModule;
	}
};

