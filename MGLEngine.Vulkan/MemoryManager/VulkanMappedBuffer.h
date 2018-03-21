#pragma once
#include <MGLEngine.Shared/Utils/Arrays/IArray.h>
#include "../MemoryManager/VulkanMemoryManager.h"
#include <vulkan/vulkan.h>
#include "../VulkanContext/VulkanLogicalDevice.h"


/*
* Since this memory is auto sync with the gpu, we make this buffer a specialization of IArray<T>
*/
class VulkanLogicalDevice;

template<class T>
class VulkanMappedBuffer : public IArray<T>
{



		VulkanMemoryManager* _memMngr;
		MemoryHandle _memHandle;
		VkBuffer _handle;
		std::vector<VkBufferUsageFlagBits> _bufferUsage;
		uint64_t _size;
		uint64_t _sizeInBytes;


	public:

		VulkanMappedBuffer<T> & operator=(const VulkanMappedBuffer<T>&) = delete;
		VulkanMappedBuffer(const VulkanMappedBuffer<T>&) = delete;

		VulkanMappedBuffer(
			VulkanMemoryManager *mngr,
			uint64_t size,
			std::vector<VkBufferUsageFlagBits> bufferUsage
		)
		{
			_size = size;
			_sizeInBytes = size * sizeof(T);
			_memMngr = mngr;
			assert(size > 0);

			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = _sizeInBytes;
			bufferInfo.usage = FromBitFlagsToInt(bufferUsage);
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			auto err = vkCreateBuffer(mngr->GetLogicalDevice()->GetHandle(), &bufferInfo, nullptr, &_handle);
			AssertVulkanSuccess(err);

			//Allocate buffer
			std::vector<enum VkMemoryPropertyFlagBits> memProperties = { VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
			_memHandle = mngr->Allocate(_handle, memProperties);


		}

		IArray<T> GetMappedArray()
		{
			return _memHandle.Map(_size);
		}

		void Flush()
		{
			return _memHandle.Flush();
		}


		uint64_t GetSize()
		{
			return _size;
		}

	
		~VulkanMappedBuffer()
		{
			vkDestroyBuffer(_memMngr->GetLogicalDevice()->GetHandle(), _handle, nullptr);
			_memHandle.Free();
		}

		int GetAlignment()
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
			return std::find(_bufferUsage.begin(), _bufferUsage.end(), VK_BUFFER_USAGE_TRANSFER_DST_BIT) != _bufferUsage.end();
		}

	};





