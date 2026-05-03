#include <map>
#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>

class ByteCodeData {
public:
	VkShaderModule vkHandle;
	uint32_t byteCodeSize;
	const uint32_t* pByteCode;
};

class ByteCodeCollection {

	std::map<const uint32_t*, ByteCodeData> _byteCodes;
	VulkanLogicalDevice* _pLogicalDevice;

public:

	ByteCodeCollection(VulkanLogicalDevice* logicalDevice);
	ByteCodeData GetByteCode(uint32_t* byteCode);
	VkShaderModule AddByteCode(const uint32_t* pByteCode, uint32_t size);
	~ByteCodeCollection();
};