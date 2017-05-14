#include "FragmentShaderByteCode.h"
#include "../VulkanUtils.h"


FragmentShaderByteCode::FragmentShaderByteCode(const VulkanLogicalDevice &device,uint32_t* p, int size)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = size;
	createInfo.pCode = p;
	auto err = vkCreateShaderModule(device.GetHandle(), &createInfo, nullptr, &_vkModule);
	AssertVulkanSuccess(err);
}


FragmentShaderByteCode::~FragmentShaderByteCode()
{
}
