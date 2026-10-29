#include <MGLEngine.Vulkan/VulkanContext/vmausage.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanImage.h>
#include <MGLEngine.Shared/Utils/pointers.h>
class VulkanLogicalDevice;
class VulkanInstance;
class VulkanMemoryAllocator {
	const VulkanLogicalDevice& _device;
	VmaAllocator _allocator;
	s_ptr<VulkanBuffer> CreateBuffer(VkBufferCreateInfo* pCreateInfo, VmaAllocationCreateInfo* pAllocInfo);
	public:
		VulkanMemoryAllocator(const VulkanLogicalDevice& device);
		~VulkanMemoryAllocator();
		s_ptr<VulkanBuffer> CreateVertexBuffer(uint64_t sizeInBytes);
		s_ptr<VulkanBuffer> CreateIndexBuffer(uint64_t numOfBytes);
		s_ptr<VulkanBuffer> CreateStagingBuffer(uint64_t sizeInBytes);
		s_ptr<VulkanBuffer> CreateUniformBuffer(uint64_t sizeInBytes);
		s_ptr<VulkanImage> CreateImageBuffer(VkImageCreateInfo imgInfo);
		s_ptr<VulkanImage> CreateImageBuffer(uint64_t sizeInBytes);
		const VulkanLogicalDevice& GetDevice() {
			return _device;
		}
	
		VmaAllocator& GetVmaAllocator() {
			return _allocator;
		}

};