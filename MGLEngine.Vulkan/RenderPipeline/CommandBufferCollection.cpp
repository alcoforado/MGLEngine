#include "CommandBufferCollection.h"
#include "VulkanPipeline.h"

CommandBufferCollection::CommandBufferCollection(const VulkanCommandPool* pool, const VulkanPipeline* pipeline, glm::vec4 color)
:_framebuffers(*(pipeline->GetVulkanSwapChainFramebuffers()))
{
	for (int i = 0; i<_framebuffers.Size(); i++)
	{
		auto framebuffer = _framebuffers.GetFramebuffer(i);
		VulkanCommandBuffer comm(pool);
		comm.BeginRenderPass(framebuffer, color);
		comm.BindPipeline(pipeline);
		_commands.push_back(comm);
	}
}



CommandBufferCollection::~CommandBufferCollection()
{
}
