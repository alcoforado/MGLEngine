#pragma once
#include <list>
#include <MGLEngine.Shared/Utils/Arrays/IArray.h>
#include <vulkan/vulkan.h>

class VulkanMemoryBlock;
class VulkanMemoryChunk;
class VulkanLogicalDevice;

class VulkanMemoryChunk
{
	friend class MemoryHandle;
	friend class VulkanMemoryBlock;
	friend class VulkanMemoryManager;
	uint64_t _totalFree;
	uint64_t _size;
	uint64_t _maxBlockSize;
	VulkanMemoryBlock* _pBiggestBlock;
	std::list<VulkanMemoryBlock*> _blocks;
	VkMemoryAllocateInfo _allocInfo;
	VkDeviceMemory _memoryHandle;
	bool _isMapped;
	char* _data;
	VulkanMemoryManager* _parent;


	explicit VulkanMemoryChunk(VulkanMemoryManager* parent, uint32_t memoryTypeIndex, uint64_t size);
	void ComputeFreeBlocksSize();
	VulkanMemoryBlock* TryToAllocate(uint32_t memoryTypeIndex, uint64_t alignment, uint64_t size);
	void Map();
	uint32_t GetMemoryTypeIndex() { return _allocInfo.memoryTypeIndex; }
	void Flush(size_t offset, size_t sizeInBytes);
};

//typedef const VulkanMemoryBlock* MemoryHandle;
class VulkanMemoryBlock
{
	friend class VulkanMemoryChunk;

	uint64_t Off;        //The offset where the memory block starts, not necessary the offset where the buffer should start. It is not necesseraly consisten with memory alignemnt 
	uint64_t AlignedOff; //Offset of the chunk block consistent with the memory requirement alignment.
	uint64_t TotalSize;  //Total size of the memory block
	uint64_t Size;       //Size in bytes of the buffer allocated with it.   
	bool IsFree;
	uint64_t AlignmentOffset;
	VulkanMemoryChunk* _chunk;

	VulkanMemoryBlock(VulkanMemoryChunk* chunk, uint64_t lOff, uint64_t lSize)
	{
		this->Off = lOff;
		this->AlignedOff = this->Off;
		this->Size = lSize;
		this->_chunk = chunk;
		this->TotalSize = lSize;
		this->AlignmentOffset = 0;
		this->IsFree = true;
	};


public:
	template<class T>
	IArray<T> Map(uint64_t nElems)
	{
		assert(!IsFree);
		_chunk->Map();
		assert(nElems <= Size / sizeof(T));
		return IArray<T>(reinterpret_cast<T*>(_chunk->_data + AlignedOff), nElems, Size / sizeof(T));
	}

	void BindBuffer(VkBuffer uint64) const;
	void Free();
	uint64_t GetOffset() const;
	uint64_t GetAlignedOffset() const { return this->AlignedOff; }
	uint64_t GetSizeInByte() const { return this->Size; }
	VulkanMemoryChunk* GetChunk() const { return _chunk; }
	//IBinding Resource;
};

class MemoryHandle
{
	friend class VulkanMemoryManager;
	VulkanMemoryBlock *_block;
	void BindBuffer(VkBuffer buff) const;

public:
	template<class T>
	IArray<T> Map(uint64_t nElems)
	{
		

		return this->_block->Map<T>(nElems);
	}
	
	MemoryHandle(VulkanMemoryBlock *block=nullptr)
	{
		_block = block;
	}
	void Free();
	uint64_t GetOffset() const;
	
	

	void Flush();
};













class VulkanMemoryManager
{

	uint64_t _blockSize;
	std::list<VulkanMemoryChunk*> _chunks;
	const VulkanLogicalDevice& _device;
	MemoryHandle Allocate(uint32_t memoryTypeIndex, uint64_t alignment, uint64_t size);
public:
	VulkanMemoryManager(VulkanLogicalDevice& device, int blockSizeInBytes);
	~VulkanMemoryManager();
	const VulkanLogicalDevice* GetLogicalDevice() const { return &_device; }
	MemoryHandle Allocate(VkBuffer buffer, std::vector<enum VkMemoryPropertyFlagBits> flags);
};


extern const int _MB; 


