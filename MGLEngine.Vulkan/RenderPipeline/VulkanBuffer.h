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
class VulkanBuffer : public IArray<T>
{

	VulkanMemoryManager* _memMngr;
	MemoryHandle _memHandle;
	VkBuffer _handle;
	std::vector<VkBufferUsageFlagBits> _bufferUsage;

	
	

public:

	VulkanBuffer & operator=(const VulkanBuffer&) = delete;
	VulkanBuffer(const VulkanBuffer&) = delete;

	VulkanBuffer(
		VulkanMemoryManager *mngr, 
		uint64_t size,uint64_t capacity, 
		std::vector<VkBufferUsageFlagBits> bufferUsage,
		std::vector<enum VkMemoryPropertyFlagBits> memProperties
		
		)
	{
		_memMngr = mngr;
		assert(capacity > 0);

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = capacity*sizeof(T);
		bufferInfo.usage = FromBitFlagsToInt(bufferUsage);
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		auto err = vkCreateBuffer(mngr->GetLogicalDevice().GetHandle(), &bufferInfo, nullptr, &_handle);
		AssertVulkanSuccess(err);

		//Allocate buffer
		_memHandle =  mngr->Allocate(_handle, memProperties);

		auto a = _memHandle.Map<T>(size);
		a.swap(*this);
		this->Resize(size);
	}

	VulkanBuffer(VulkanMemoryManager *mngr,	uint64_t size, uint64_t capacity)
		:VulkanBuffer(mngr,size,capacity,{VK_BUFFER_USAGE_VERTEX_BUFFER_BIT},{ VK_MEMORY_PROPERTY_HOST_COHERENT_BIT , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT})
	{
		
	}

	~VulkanBuffer()
	{
		vkDestroyBuffer(_memMngr->GetLogicalDevice().GetHandle(), _handle, nullptr);
		_memHandle.Free();
		this->clear();
	}
	
	int GetAlignment()
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(_memMngr->GetLogicalDevice().GetHandle(), _handle, &memRequirements);
		return static_cast<int>(memRequirements.alignment);

	}

	void Sync()
	{
		throw new Exception("Not Implemented");
	}

	VkBuffer GetHandle() const { return _handle; }
	MemoryHandle GetMemoryHandle() const { return _memHandle; }
	VulkanMemoryManager* GetMemoryManager() const { return _memMngr; }
	std::vector<VkBufferUsageFlagBits> GetBufferUsage() const {
		return _bufferUsage;
	}
	bool IsStaging()
	{
		return std::find(_bufferUsage.begin(), _bufferUsage.end(), VK_BUFFER_USAGE_TRANSFER_DST_BIT)!=_bufferUsage.end();
	}

};



