#pragma once
#include <MGLEngine.Vulkan/RenderPipeline/VulkanBuffer.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMappedAutoSyncBuffer.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>
/*
* As the name implies, this is a buffer with GPU only access, making this memory the best efficient
* memory you can have inside the GPU but the CPU cannot access directly. 
* The only way to copy data to this buffer is using a temporary cpu/gpu mapped memory. First copy data from the CPU to this shared memory and then use a command queue buffer to make
* the gpu to copy all memory from the shared buffer to the gpu only buffer.   
* 
* Therefore this is a fast read/write GPU but has slow copy from CPU to GPU.
*/

	template<class T>
	class VulkanGPUBuffer 
	{
		VulkanBuffer<T> _buffer;
	public:
		VulkanGPUBuffer(
			VulkanMemoryManager *mngr,
			uint64_t size, uint64_t capacity,
			std::vector<VkBufferUsageFlagBits> bufferUsage)
			:_buffer(mngr, capacity, Concat(bufferUsage, { VK_BUFFER_USAGE_TRANSFER_DST_BIT }), { VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT })
		{
			
		}

		/*
		 * Copy the data in the VulkanMappedAutoSyncBuffer to the gpu exclusive memory.
		 * The buffer must be a staging buffer (has the VK_BUFFER_USAGE_TRANSFER_SRC_BIT usage bit)
		 * and must be of the same size
		 */
		void Sync(VulkanMappedAutoSyncBuffer<T> &srcBuffer)
		{
			if (srcBuffer.size() != _buffer.size())
			{
				throw new Exception("buffers size are not equal");
			}
			if(!srcBuffer.IsStaging())
			{
				throw new Exception("buffer is not a staging buffer (VK_BUFFER_USAGE_TRANSFER_SRC_BIT)");
			}
			OPointer<VulkanCommandBuffer> cb = _buffer.GetMemoryManager()->GetLogicalDevice().GetGraphicCommandPool()->CreateCommandBuffer(VulkanCommandBufferOptions().OneTimeSubmit());
			cb->CopyBuffers(srcBuffer.GetVulkanBuffer().GetHandle(), _buffer.GetHandle(), _buffer.SizeInBytes());
			cb->End();
			
			const VulkanQueue *queue = _buffer.GetMemoryManager()->GetLogicalDevice()->GetGraphicQueue();
			queue->Submit(cb);
			queue->WaitIdle();
			

		}



		/*
		 * This is the most expensive memory copy method in the library.
		 * Uses a staging mapped cpu gpu to copy to the gpu only memory
		 */
		void Sync(const std::vector<T> &v)
		{
			

		}


};