#include "VulkanMemoryManager.h"
#include <algorithm>


VulkanMemoryManager::VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeMB)
:_device(device)
{
	_blockSize = blockSizeMB* 1048576;
}


VulkanMemoryManager::~VulkanMemoryManager()
{
}

void VulkanMemoryManager::Allocate(uint64_t size)
{
	for (VulkanMemoryChunk *chunk : _chunks)
	{
		if (size <= chunk->_maxBlockSize)
		{
			if (chunk->TryToAllocate(size))
			{
				return;
			}
		}
	}

	//
	_chunks.push_back(new VulkanMemoryChunk(std::max(_blockSize, size)));


}
