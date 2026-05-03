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
