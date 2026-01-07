#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryProperties.h>

class VulkanMemoryAllocator;
class VulkanBuffer {
	friend class VulkanMemoryAllocator;
private:

	VkBuffer _buffer;
	uint32_t _size;
	VmaAllocator* _pAllocator;
	VulkanMemoryProperties _memType;
	uint32_t _deviceMemoryTypeIndex;
	VkBufferUsageFlags _usage;
	VmaAllocation _allocation;
	VmaAllocationInfo _allocationInfo;
	void* _pMappedData;
public:
	VulkanBuffer() {
		_memType = {};
		_pAllocator = nullptr;
		_pMappedData = nullptr;
		_buffer = VK_NULL_HANDLE;
	}

	void* Map();

	void Unmap();

	void DeleteIfNecessary()
	{
		if (_pAllocator && _buffer != VK_NULL_HANDLE)
		{
			vmaDestroyBuffer(*_pAllocator, _buffer, _allocation);
			_pAllocator == nullptr;
			_buffer = VK_NULL_HANDLE;
		}
	}

};