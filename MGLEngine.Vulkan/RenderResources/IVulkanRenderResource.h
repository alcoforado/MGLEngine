#pragma once
#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanResourceLoadContext.h>

class VulkanCommandBuffer;


class IVulkanRenderResource : public IRenderResource
{
public:
	virtual void Load(IVulkanResourceLoadContext *context) = 0;
	virtual VkDescriptorSetLayoutBinding GetVulkanDescriptor()  const = 0;
	
};
