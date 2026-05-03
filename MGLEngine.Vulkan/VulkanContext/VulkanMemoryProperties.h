#pragma once
#include <vulkan/vulkan.h>

class Heap
{
	uint64_t size;
	bool DeviceLocal; 
	bool MultiInstance; 
};

class VulkanMemoryProperties
{
public:
	uint32_t MemFlags;
	bool DeviceLocal;
	bool HostVisible;
	bool HostCoherent;
	bool HostCached;
	bool LazilyAllocated;
	bool HeapMultiInstance;
	bool HeapLocal;
	uint64_t HeapSize;
	VulkanMemoryProperties(VkFlags flags,VkMemoryHeap heap);
	~VulkanMemoryProperties();
	VulkanMemoryProperties() {
		
	}
};

