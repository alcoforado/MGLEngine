#pragma once
#include "MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h"

class IVulkanRenderResourceLoadContext
{



public:
	virtual VulkanCommandBuffer* GetLoadCommandBuffer() = 0;
};


class VulkanRenderResourceLoadContext : IVulkanRenderResourceLoadContext
{
public :
	OPointer<VulkanCommandBuffer> _loadCommandBuffer;

	virtual  VulkanCommandBuffer* GetLoadCommandBuffer() override
	{
		return _loadCommandBuffer;
	}
};

