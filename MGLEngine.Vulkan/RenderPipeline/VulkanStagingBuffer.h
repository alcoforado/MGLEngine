#pragma once
#include "CommandBufferCollection.h"
#include "Utils/Arrays/IArray.h"
#include "../MemoryManager/VulkanMemoryManager.h"
class VulkanMemoryManager;
class VulkanLogicalDevice;

class VulkanStagingBuffer
{
	VulkanMemoryManager* _memMngr;
	MemoryHandle _memHandle;
	VkBuffer _handle;
	uint64_t _size;
	void *_data;
	void AllocBuffer(VulkanMemoryManager *mngr, uint64_t size);
	void clear();
public:
	VulkanStagingBuffer(VulkanMemoryManager *mngr, uint64_t size);
	~VulkanStagingBuffer();
	void resize(uint64_t size);
	
	
	
	void Sync();


};

