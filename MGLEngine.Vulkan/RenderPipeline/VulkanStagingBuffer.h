#pragma once
#include <MGLEngine.Shared/Utils/Arrays/IArray.h>
#include "../MemoryManager/VulkanMemoryManager.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"
#include <MGLEngine.Shared/Utils/Exception.h>
#include "../VulkanUtils.h"
#include "../MemoryManager/VulkanMemoryManager.h"
class VulkanLogicalDevice;

template<class T>
class VulkanStagingBuffer : public IArray<T>
{

	VulkanMemoryManager* _memMngr;
	MemoryHandle _memHandle;
	VkBuffer _handle;
private:

	
	

public:

	VulkanStagingBuffer & operator=(const VulkanStagingBuffer&) = delete;
	VulkanStagingBuffer(const VulkanStagingBuffer&) = delete;

	VulkanStagingBuffer(VulkanMemoryManager *mngr, uint64_t size,uint64_t capacity)
	{
		_memMngr = mngr;
		assert(capacity > 0);

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = capacity*sizeof(T);
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		auto err = vkCreateBuffer(mngr->GetLogicalDevice().GetHandle(), &bufferInfo, nullptr, &_handle);
		AssertVulkanSuccess(err);

		//Allocate buffer
		_memHandle =  mngr->Allocate(_handle, { VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT });

		auto a = _memHandle.Map<T>(size);
		a.swap(*this);
		this->Resize(size);
	}

	~VulkanStagingBuffer()
	{
		vkDestroyBuffer(_memMngr->GetLogicalDevice().GetHandle(), _handle, nullptr);
		_memHandle.Free();
		this->clear();
	}
	
	int GetAlignment()
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(_memMngr->GetLogicalDevice().GetHandle(), _handle, &memRequirements);
		return memRequirements.alignment;

	}

	void Sync()
	{
		throw new Exception("Not Implemented");
	}

	VkBuffer GetHandle() const { return _handle; }
	
};

