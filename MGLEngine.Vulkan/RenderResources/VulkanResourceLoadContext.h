#pragma once
#include "MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h"
#include <vulkan/vulkan.h>
class IVulkanResourceLoadContext
{

public:
	virtual VulkanCommandBuffer* GetLoadCommandBuffer() = 0;
	
};


class VulkanRenderResourceLoadContext : IVulkanResourceLoadContext
{
	OPointer<VulkanCommandBuffer> _loadCommandBuffer;
public :

	virtual  VulkanCommandBuffer* GetLoadCommandBuffer() override
	{
		return _loadCommandBuffer;
	}


};

