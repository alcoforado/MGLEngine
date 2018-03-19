#include <MGLEngine.Vulkan/MemoryManager/VulkanBuffer.h>

/*
 * Since this memory is auto sync with the gpu, we make this buffer a specialization of IArray<T>
 * NO SYNC FUNCTIONS ARE NECESSARY, THIS IS DONE AUTOMATICALLY BY THE HARDWARE	
 */

template<class T>
class VulkanMappedAutoSyncBuffer : public IArray<T>
{
	VulkanBuffer<T> _buffer;
public:
	VulkanMappedAutoSyncBuffer(
		VulkanMemoryManager *mngr,
		uint64_t size, uint64_t capacity,
		std::vector<VkBufferUsageFlagBits> bufferUsage)
		:_buffer(mngr,capacity,bufferUsage,{VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT})
	{
		assert(capacity >= size);
		auto a = _buffer.GetMemoryHandle().Map<T>(capacity);
		a.swap(*this);
		this->Resize(size);
	}
	
	~VulkanMappedAutoSyncBuffer()
	{
		this->clear();

	}
	
	int GetAlignment()
	{
		return _buffer.GetAlignment();
	}

	VkBuffer GetHandle()
	{
		return _buffer.GetHandle();
	}

	bool IsStaging()
	{
		return _buffer.IsStaging();
	}
};