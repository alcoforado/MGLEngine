#pragma once
#include "Utils/Arrays/IArray.h"
#include "../MemoryManager/VulkanMemoryManager.h"
#include <vulkan/vulkan.h>
class VulkanLogicalDevice;

class VulkanStagingBuffer
{

	VulkanMemoryManager* _memMngr;
	MemoryHandle _memHandle;
	VkBuffer _handle;
	uint64_t _size;
	void *_data;
	void AllocBuffer(VulkanMemoryManager *mngr, uint64_t sizeInBytes);
	void clear();
public:
	VulkanStagingBuffer(VulkanMemoryManager *mngr, uint64_t sizeInBytes);
	~VulkanStagingBuffer();
	void resize(uint64_t size);
	
	template<class T>
	IArray<T> ToArray()
	{
		return _memHandle->Map<T>();
	}
	
	template<class T>
	IArray<T> ToArray(int size)
	{
		auto result = _memHandle->Map<T>();
		result.Resize(size);
	}

	
	void Sync();
	VkBuffer GetHandle() const;
	VkDeviceSize GetOff() const;
};

