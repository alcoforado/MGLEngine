#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include "IVulkanSlotBinding.h"
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
	std::vector<IVulkanSlotBinding*> _bindings;
	void InitializeDescriptorSet(VkDescriptorSet dsHandle);
	VulkanDescriptorSet(VulkanDescriptorSetLayout *pLayout);
	~VulkanDescriptorSet();
public:
	VulkanDescriptorSetLayout* GetLayout() const { return _pLayout; }
	VkDescriptorSet GetDescriptorSetHandle() const { return _dsHandle; }
	const std::vector<IVulkanSlotBinding*>& GetBindings() { return _bindings; }
};

