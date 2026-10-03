#include "VulkanBuffer.h"
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>

void* VulkanBuffer::Map() {
	eassert(_buffer != VK_NULL_HANDLE, "Cant map empty buffer");
	
	if (_pMappedData)
		return _pMappedData;
	eassert(_memType.HostVisible, std::format("This buffer is not host visible and cannot be mapped"));
	vmaMapMemory(*_pAllocator, _allocation,&_pMappedData);
	return _pMappedData;
}

void VulkanBuffer::Unmap()
{
	if (_pMappedData == nullptr)
		return; //nothing to do
	vmaUnmapMemory(*_pAllocator, _allocation);
	_pMappedData = nullptr;

}

//Flush the vector memory. 
//As a caller always assume the buffer needs to flush.
//If the memory is host coherent than calling flush amount to nothing.
void VulkanBuffer::Flush()
{
	eassert(_pMappedData != nullptr, "Invalid Operation Flush: Buffer is not mapped, call the Map() function first");
	
	VkResult result = vmaFlushAllocation(*_pAllocator, _allocation, 0, VK_WHOLE_SIZE);
	AssertVulkanSuccess(result);


//If the buffer is memory coherent calling vmaFlushAllocation will result in nothing

}

void VulkanBuffer::ToGPU(void* pSrc, uint64_t sizeInBytes)
{
	eassert(_memType.HostVisible, std::format("This buffer is not host visible and cannot be mapped"));
	eassert(sizeInBytes < this->_size, std::format("Overflow detected"));
	void* pDst = this->Map();
	memcpy(pDst, pSrc, sizeInBytes);
	this->Unmap();


}

void VulkanBuffer::Delete() {
	if (_buffer == VK_NULL_HANDLE)
		return;
	this->Unmap();
	vmaDestroyBuffer(*_pAllocator, _buffer, _allocation);
	_pAllocator = nullptr;
	_buffer = VK_NULL_HANDLE;
}