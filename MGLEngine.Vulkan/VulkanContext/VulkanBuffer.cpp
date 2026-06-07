#include "VulkanBuffer.h"
#include <MGLEngine.Shared/Utils/eassert.h>

void* VulkanBuffer::Map() {
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


void VulkanBuffer::ToGPU(void* pSrc, uint64_t sizeInBytes)
{
	eassert(_memType.HostVisible, std::format("This buffer is not host visible and cannot be mapped"));
	eassert(sizeInBytes < this->_size, std::format("Overflow detected"));
	void* pDst = this->Map();
	memcpy(pDst, pSrc, sizeInBytes);
	this->Unmap();


}