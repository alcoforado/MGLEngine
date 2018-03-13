#pragma once

enum  GPUMemoryType { GPU_ONLY, MAPPED_MEMORY, AUTO_SYNC_MEMORY };
class IRenderResource
{
public:
	
	virtual ~IRenderResource() = 0;
	virtual bool IsDirty() = 0;
	virtual void Clear()=0;
	virtual GPUMemoryType MemoryType() = 0;
};