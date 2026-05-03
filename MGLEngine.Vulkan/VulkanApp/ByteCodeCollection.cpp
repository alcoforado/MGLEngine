#include "ByteCodeCollection.h"
#include <exception>

ByteCodeCollection::ByteCodeCollection(VulkanLogicalDevice* logicalDevice)
	: _pLogicalDevice(logicalDevice)
{
}

ByteCodeData ByteCodeCollection::GetByteCode(uint32_t* byteCode)
{
	if (_byteCodes.find(byteCode) == _byteCodes.end())
	{
		throw std::exception("Byte code not found");
	}
	return _byteCodes[byteCode];
}

VkShaderModule ByteCodeCollection::AddByteCode(const uint32_t* pByteCode, uint32_t size)
{
	if (_byteCodes.contains(pByteCode))
	{
		return _byteCodes[pByteCode].vkHandle;
	}
	else
	{
		ByteCodeData data{
			.vkHandle = VK_NULL_HANDLE,
			.byteCodeSize = size,
			.pByteCode = pByteCode
		};
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = size;
		createInfo.pCode = pByteCode;

		auto err = vkCreateShaderModule(_pLogicalDevice->GetHandle(), &createInfo, nullptr, &(data.vkHandle));
		AssertVulkanSuccess(err);

		_byteCodes[pByteCode] = data;
		return data.vkHandle;
	}
}
ByteCodeCollection::~ByteCodeCollection()
{
		for (auto& pair : _byteCodes) {
			if (pair.second.vkHandle != VK_NULL_HANDLE) {
				vkDestroyShaderModule(_pLogicalDevice->GetHandle(), pair.second.vkHandle, nullptr);
			}
		}
}
