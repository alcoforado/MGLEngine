#include <vma/vk_mem_alloc.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
class VulkanLogicalDevice;
class VulkanInstance;

class VulkanMemoryAllocator {
	const VulkanLogicalDevice& _device;
	VmaAllocator _allocator;
	public:
		VulkanMemoryAllocator(const VulkanLogicalDevice& device);
		~VulkanMemoryAllocator();
		VulkanBuffer CreateBuffer(VkBufferCreateInfo* pCreateInfo, VmaAllocationCreateInfo* pAllocInfo);
		VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
		VulkanBuffer CreateIndexBuffer(uint64_t numOfIndices);

};