#include "VulkanStagingBuffer.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "Utils/Exception.h"
#include "../VulkanUtils.h"

void VulkanStagingBuffer::AllocBuffer(VulkanLogicalDevice &device, long size)
{
	_size = size;
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	auto err = vkCreateBuffer(device.GetHandle(), &bufferInfo, nullptr, &_handle);
	AssertVulkanSuccess(err);

	//Allocate buffer

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device.GetHandle(), _handle, &memRequirements);

	auto memProperties = device.GetPhysicalDevice().GetMemoryProperties();
	VulkanMemoryProperties *pMem = nullptr;
	uint32_t i;
	for (i = 0; i < memProperties.size(); i++) {
		if ((memRequirements.memoryTypeBits & (1 << i)) && (memProperties[i].HostCoherent && memProperties[i].HostVisible)) {
			pMem = &memProperties[i];
			break;
		}
	}
	if (pMem == nullptr)
	{
		throw new Exception("No memory for vertex buffer was found");
	}
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = i;

	err = vkAllocateMemory(device.GetHandle(), &allocInfo, nullptr, &_memoryHandle);
	AssertVulkanSuccess(err);

	vkBindBufferMemory(device.GetHandle(), _handle, _memoryHandle, 0);
}

VulkanStagingBuffer::VulkanStagingBuffer(VulkanLogicalDevice &device,long size)
	:_device(device)
{
	AllocBuffer(device,size);



}



VulkanStagingBuffer::~VulkanStagingBuffer()
{
	clear();

}

void VulkanStagingBuffer::clear()
{
	vkDestroyBuffer(_device.GetHandle(), _handle, nullptr);
	vkFreeMemory(_device.GetHandle(), _memoryHandle, nullptr);
	_size = 0;
}

void VulkanStagingBuffer::resize(size_t size)
{
	clear();
	AllocBuffer(_device, size);
}


