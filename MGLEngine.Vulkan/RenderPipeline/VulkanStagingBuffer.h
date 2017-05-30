#pragma once
#include "CommandBufferCollection.h"
#include "Utils/Arrays/IArray.h"
class VulkanLogicalDevice;

class VulkanStagingBuffer
{
	VkDeviceMemory _memoryHandle;
	VulkanLogicalDevice&  _device;
	VkBuffer _handle;
	long _size;
	void *_data;
	void AllocBuffer(VulkanLogicalDevice &device, long size);
public:
	VulkanStagingBuffer(VulkanLogicalDevice &device,long size);
	~VulkanStagingBuffer();
	void clear();
	void resize(size_t size);
	
	template<class T>
	IArray<T> GetArray()
	{
		if (_data==nullptr)
		{
			vkMapMemory(_device.GetHandle(), _memoryHandle, 0, _size, 0, &_data);
		}
		return IArray<T>(reinterpret_cast<T*>(_data), _size);
	}
	
	void Sync();


};

