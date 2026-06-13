#pragma once
#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/vmausage.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryProperties.h>

class VulkanMemoryAllocator;
class VulkanBuffer {
	friend class VulkanMemoryAllocator;
private:

	VkBuffer _buffer;
	VkDeviceSize _size;
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
		_size = 0;
	}
	VkBuffer GetHandle() {
		return _buffer;
	}
	void* Map();

	void Unmap();

	bool Empty() {
		return _size == 0;
	}

	VkDeviceSize GetSizeInBytes() {
		return _size;
	}

	void ToGPU(void* pData, uint64_t sizeInBytes);
	


	void Delete()
	{
		if (_buffer == VK_NULL_HANDLE)
			return;
		vmaDestroyBuffer(*_pAllocator, _buffer, _allocation);
		_pAllocator = nullptr;
		_buffer = VK_NULL_HANDLE;

	}

};