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

VulkanBuffer VulkanMemoryAllocator::CreateBuffer(VkBufferCreateInfo* pCreateInfo, VmaAllocationCreateInfo* pAllocInfo)
{
	

	VkBuffer buffer;
	VmaAllocation allocation;
	VmaAllocationInfo allocInfoResult;
	vmaCreateBuffer(_allocator, pCreateInfo, pAllocInfo, &buffer, &allocation, &allocInfoResult);
	VulkanBuffer vb;
	vb.buffer = buffer;
	vb.size = (uint32_t)pCreateInfo->size;
	vb.usage = pCreateInfo->usage;
	vb.allocation = allocation;
	vb.allocationInfo = allocInfoResult;
	vb.deviceMemoryTypeIndex = allocInfoResult.memoryType;
	return vb;
}

VulkanBuffer VulkanMemoryAllocator::CreateVertexBuffer(uint64_t sizeInBytes)
{
	VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
	bufferInfo.size = sizeInBytes;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	

	VmaAllocationCreateInfo allocInfo = {};
	allocInfo.usage = VMA_MEMORY_USAGE_AUTO;
	allocInfo.flags= VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;

	return CreateBuffer(&bufferInfo, &allocInfo);
}

VulkanBuffer VulkanMemoryAllocator::CreateIndexBuffer(uint64_t numOfIndices)
{
	VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
	bufferInfo.size = numOfIndices*sizeof(uint32_t);
	bufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;


	VmaAllocationCreateInfo allocInfo = {};
	allocInfo.usage = VMA_MEMORY_USAGE_AUTO;
	allocInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;

	return CreateBuffer(&bufferInfo, &allocInfo);
	
}



