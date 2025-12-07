#include "VulkanMemoryAllocator.h"
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>

VulkanMemoryAllocator::VulkanMemoryAllocator(const VulkanLogicalDevice& device)
	:_device(device)
{
	VmaAllocatorCreateInfo allocatorCreateInfo = {};
	allocatorCreateInfo.flags = VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT;
	allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_0;
	allocatorCreateInfo.physicalDevice = device.GetPhysicalDevice().GetHandle();
	allocatorCreateInfo.device = device.GetHandle();
	allocatorCreateInfo.instance = device.GetPhysicalDevice().GetVulkanInstance().GetHandle();

	VkResult err=vmaCreateAllocator(&allocatorCreateInfo, &_allocator);
	AssertVulkanSuccess(err);
}

VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
	vmaDestroyAllocator(_allocator);
}

VulkanBuffer VulkanMemoryAllocator::CreateBuffer(VkBufferCreateInfo* pCreateInfo, VmaMemoryUsage vmaUsage, uint64_t sizeInBytes)
{
	VmaAllocationCreateInfo allocInfo = {};
	allocInfo.usage = vmaUsage;

	VkBuffer buffer;
	VmaAllocation allocation;
	VmaAllocationInfo allocInfoResult;
	vmaCreateBuffer(_allocator, pCreateInfo, &allocInfo, &buffer, &allocation, &allocInfoResult);
	VulkanBuffer vb;
	vb.buffer = buffer;
	vb.size = (uint32_t)sizeInBytes;
	vb.allocation = allocation;
	vb.deviceMemoryTypeIndex = allocInfoResult.memoryType;
	return vb;
}
