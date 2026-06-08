#include <MGLEngine.Vulkan/VulkanContext/vmausage.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanImage.h>

class VulkanLogicalDevice;
class VulkanInstance;
class VulkanMemoryAllocator {
	const VulkanLogicalDevice& _device;
	VmaAllocator _allocator;
	VulkanBuffer CreateBuffer(VkBufferCreateInfo* pCreateInfo, VmaAllocationCreateInfo* pAllocInfo);
	public:
		VulkanMemoryAllocator(const VulkanLogicalDevice& device);
		~VulkanMemoryAllocator();
		VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
		VulkanBuffer CreateIndexBuffer(uint64_t numOfIndices);
		VulkanBuffer CreateStagingBuffer(uint64_t sizeInBytes);
		VulkanImage CreateImageBuffer(VkImageCreateInfo imgInfo);
		VulkanImage CreateImageBuffer(uint64_t sizeInBytes);
		const VulkanLogicalDevice& GetDevice() {
			return _device;
		}
	

};