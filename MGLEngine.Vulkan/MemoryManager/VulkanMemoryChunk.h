#pragma once
class VulkanMemoryManager;
class VulkanMemoryChunk
{
	friend class VulkanMemoryManager;
	uint64_t _totalFree;
	uint64_t _size;
	uint64_t _maxBlockSize;
	std::list<VulkanMemoryBlock> _blocks;
	VulkanMemoryChunk();
};