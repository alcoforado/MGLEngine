#include "VulkanStagingBuffer.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include "Utils/Exception.h"
#include "../VulkanUtils.h"
#include "../MemoryManager/VulkanMemoryManager.h"

void VulkanStagingBuffer::AllocBuffer(VulkanMemoryManager *mngr, uint64_t size)
{
	_size = size;
	_data = nullptr;
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	auto err = vkCreateBuffer(mngr->GetLogicalDevice().GetHandle(), &bufferInfo, nullptr, &_handle);
	AssertVulkanSuccess(err);

	//Allocate buffer

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(mngr->GetLogicalDevice().GetHandle(), _handle, &memRequirements);

	uint32_t i = mngr->GetLogicalDevice().GetPhysicalDevice().FindMemoryPropertyIndex(
		memRequirements.memoryTypeBits, { VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT });
	
	_memHandle=mngr->Allocate(i, memRequirements.alignment, memRequirements.size);

	_memHandle->BindBuffer(_handle);
}

VulkanStagingBuffer::VulkanStagingBuffer(VulkanMemoryManager *mngr, uint64_t size)
:_memMngr(mngr)
{
	assert(size > 0);
	AllocBuffer(mngr,size);



}



VulkanStagingBuffer::~VulkanStagingBuffer()
{
	clear();

}

void VulkanStagingBuffer::clear()
{
	assert(_size != 0); //Trying to delete empty buffer
	vkDestroyBuffer(_memMngr->GetLogicalDevice().GetHandle(), _handle, nullptr);
	_memHandle->Free();
	_size = 0;
	_data = nullptr;
}

void VulkanStagingBuffer::resize(uint64_t size)
{
	clear();
	AllocBuffer(_memMngr, size);
}

