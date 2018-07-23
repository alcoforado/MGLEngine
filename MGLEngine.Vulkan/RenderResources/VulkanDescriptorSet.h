#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include <vector>

class VulkanLogicalDevice;
class VulkanDescriptorSetPool;
class SlotManager;
class VulkanDescriptorSetLayout;
class VulkanDescriptorSet
{
	friend class VulkanDescriptorSetPool;
	VkDescriptorSet _dsHandle;
	VulkanDescriptorSetLayout *_pLayout;
	void SetDescriptorSetHandle(VkDescriptorSet dsHandle) { _dsHandle = dsHandle; }
	VulkanDescriptorSet(VulkanDescriptorSetLayout *pLayout);
	~VulkanDescriptorSet();
public:
	VulkanDescriptorSetLayout* GetLayout() const { return _pLayout; }
	VkDescriptorSet GetDescriptorSetHandle() const { return _dsHandle; }
};

