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
class VulkanBuffer 
{

	VulkanMemoryManager* _memMngr;
	MemoryHandle _memHandle;
	VkBuffer _handle;
	std::vector<VkBufferUsageFlagBits> _bufferUsage;
	uint64_t _size;
	uint64_t _sizeInBytes;
	

public:

	VulkanBuffer & operator=(const VulkanBuffer&) = delete;
	VulkanBuffer(const VulkanBuffer&) = delete;

	VulkanBuffer(
		VulkanMemoryManager *mngr, 
		uint64_t size, 
		std::vector<VkBufferUsageFlagBits> bufferUsage,
		std::vector<enum VkMemoryPropertyFlagBits> memProperties
		
		)
	{
		_size = size;
		_sizeInBytes= size * sizeof(T);
		_memMngr = mngr;
		assert(size > 0);

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = _sizeInBytes;
		bufferInfo.usage = BitwiseOr(bufferUsage);
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		auto err = vkCreateBuffer(mngr->GetLogicalDevice()->GetHandle(), &bufferInfo, nullptr, &_handle);
		AssertVulkanSuccess(err);

		//Allocate buffer
		_memHandle =  mngr->Allocate(_handle, memProperties);

		
	}

	uint64_t GetSize() const
	{
		return _size;
	}

	VulkanBuffer(VulkanMemoryManager *mngr,	uint64_t size, uint64_t capacity)
		:VulkanBuffer(mngr,size,capacity,{VK_BUFFER_USAGE_VERTEX_BUFFER_BIT},{ VK_MEMORY_PROPERTY_HOST_COHERENT_BIT , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT})
	{
		
	}

	~VulkanBuffer()
	{
		vkDestroyBuffer(_memMngr->GetLogicalDevice()->GetHandle(), _handle, nullptr);
		_memHandle.Free();
	}
	
	int GetAlignment() const
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(_memMngr->GetLogicalDevice()->GetHandle(), _handle, &memRequirements);
		return static_cast<int>(memRequirements.alignment);

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



