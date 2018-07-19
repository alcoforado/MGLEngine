#pragma once
#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanResourceLoadContext.h>

class VulkanCommandBuffer;
enum ResourceWriteFrequency {ONCE_PER_FRAME,MANY_PER_FRAME,ONCE_PER_MANY_FRAMES};

class IVulkanRenderSlot : public IRenderResource
{
	ResourceWriteFrequency _frequency;
public:

	IVulkanRenderSlot(ResourceWriteFrequency frequency)
	{
		_frequency = frequency;
	}
	
	virtual void Load(IVulkanResourceLoadContext *context) = 0;
	virtual VkDescriptorSetLayoutBinding GetVulkanDescriptor()  const = 0;
	virtual ResourceWriteFrequency WriteFrequency() const {
		return _frequency;
	}
};
