#pragma once
#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include <vulkan/vulkan.h>

class VulkanDescriptorSet;
class VulkanCommandBuffer;
class IVulkanSlotBinding;
class VulkanDescriptorSet;
enum ResourceWriteFrequency {ONCE_PER_FRAME,MANY_PER_FRAME,ONCE_PER_MANY_FRAMES};

class IVulkanRenderSlot : public IRenderResource
{
	ResourceWriteFrequency _frequency;
public:

	IVulkanRenderSlot(ResourceWriteFrequency frequency)
	{
		_frequency = frequency;
	}
	
	virtual ResourceWriteFrequency WriteFrequency() const {
		return _frequency;
	}

	virtual VkDescriptorSetLayoutBinding GetVkDescriptorSetLayoutBinding()=0;

	virtual IVulkanSlotBinding* Bind(VulkanDescriptorSet *dsSet)=0;

};
