#pragma once

enum  GPUMemoryType { GPU_ONLY, MAPPED_MEMORY, AUTO_SYNC_MEMORY };
class IRenderResource
{
public:
	
	virtual ~IRenderResource() {};
	virtual bool IsDirty() = 0;
	virtual GPUMemoryType MemoryType() = 0;
};