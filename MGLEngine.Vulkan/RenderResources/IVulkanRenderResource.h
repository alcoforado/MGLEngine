#pragma once
#pragma once
#include <MGLEngine.Shared/Utils/DrawTree/IRenderResource.h>


class VulkanCommandBuffer;

class IVulkanRenderResource : public IRenderResource
{
	virtual void WriteCommands(VulkanCommandBuffer *cb) = 0;
	
}
