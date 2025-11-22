#include "VulkanMemoryProperties.h"






VulkanMemoryProperties::VulkanMemoryProperties(VkFlags flags, VkMemoryHeap heap)
{
	MemType = flags;
	DeviceLocal = (flags&VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) != 0;
	HostVisible = (flags&VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0;
	HostCoherent= (flags&VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) != 0;
	HostCached= (flags&VK_MEMORY_PROPERTY_HOST_CACHED_BIT) != 0;
	LazilyAllocated= (flags&VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)!=0;
	HeapMultiInstance= (heap.flags&VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR)!=0;
	HeapLocal= (heap.flags&VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) != 0;
	HeapSize= heap.size;

}

VulkanMemoryProperties::~VulkanMemoryProperties()
{
}
