#include <MGLEngine.Vulkan/MemoryManager/VulkanBuffer.h>
#include <MGLEngine.Vulkan/MemoryManager/IMappedMemory.h>

/*
 * Since this memory is auto sync with the gpu, we make this buffer a specialization of IArray<T>
 * NO SYNC FUNCTIONS ARE NECESSARY, THIS IS DONE AUTOMATICALLY BY THE HARDWARE	
 */

template<class T>
class VulkanMappedAutoSyncBuffer : public IArray<T>, public IMappedMemory<T>
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
	
	virtual void Flush() override { return; }
	
	virtual IArray<T> Map() override { return *this; }



	int GetAlignment() const
	{
		return _buffer.GetAlignment();
	}

	virtual VkBuffer GetHandle() const override
	{
		return _buffer.GetHandle();
	}

	bool IsStaging() const 
	{
		return _buffer.IsStaging();
	}
	const VulkanBuffer<T>* GetVulkanBuffer() const
	{
		return &_buffer;
	}
};