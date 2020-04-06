#pragma once
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>
#include <MGLEngine.Vulkan/VulkanContext/IDrawContext.h>


#include <vulkan/vulkan.h>
class ITreeExecutionContext
{

public:
	virtual VulkanCommandBuffer* GetCommandBuffer() = 0;
	
};


class TreeExecutionContext : ITreeExecutionContext
{
	
	IDrawContext& _context;
	VulkanPipeline* _pPipeline;
	VulkanCommandBuffer* _pCommandBuffer;
public :

	TreeExecutionContext(IDrawContext* context,VulkanPipeline *pipeline)
		:_context(*context),_pPipeline(pipeline)
	{

	};

	IDrawContext& GetDrawContext() { return _context; }

	VulkanCommandBuffer* GetCommandBuffer()
	{
		return _pCommandBuffer;
	}

	 void  SetCommandBuffer(VulkanCommandBuffer *pBuffer)  {
		_pCommandBuffer = pBuffer;
	}

	 VulkanPipeline* GetPipeline() { return _pPipeline; }

};

