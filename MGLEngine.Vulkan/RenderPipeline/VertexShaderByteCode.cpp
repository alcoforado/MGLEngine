#include "VertexShaderByteCode.h"
#include "../VulkanUtils.h"
#include "../VulkanContext/VulkanLogicalDevice.h"

VertexShaderByteCode::VertexShaderByteCode(const VulkanLogicalDevice &device, uint32_t* p, int size)
:_device(device)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = size;
	createInfo.pCode = p;
	auto err = vkCreateShaderModule(device.GetHandle(), &createInfo, nullptr, &_vkModule);
	AssertVulkanSuccess(err);
}

VertexShaderByteCode::~VertexShaderByteCode()
{
	vkDestroyShaderModule(_device.GetHandle(),_vkModule,nullptr);
}
