#pragma once
#include <cstdint>
#include <vulkan/vulkan.h>

class VulkanLogicalDevice;

class VertexShaderByteCode
{
	VkShaderModule _vkModule;
	const VulkanLogicalDevice& _device;
public:
	VertexShaderByteCode(const VulkanLogicalDevice &device, const uint32_t* p, int size);
	~VertexShaderByteCode();
	VkShaderModule GetHandle() const {
		return _vkModule;
	}
};

