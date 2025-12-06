#include <vma/vk_mem_alloc.h>
class VulkanLogicalDevice;
class VulkanInstance;
class VulkanMemoryAllocator {
	const VulkanLogicalDevice& _device;
	VmaAllocator _allocator;
	public:
		VulkanMemoryAllocator(const VulkanLogicalDevice& device);
		~VulkanMemoryAllocator();
};