#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include "IVulkanSlotBinding.h"
#include <vector>
#include <cassert>
#include <MGLEngine.Shared/Utils/eassert.h>

class VulkanLogicalDevice;
class VulkanDescriptorSetPool;
class SlotManager;
class VulkanDescriptorSetLayout;
class VulkanDescriptorSet
{
	friend class VulkanDescriptorSetPool;
	VkDescriptorSet _dsHandle=nullptr;
	VulkanDescriptorSetLayout *_pLayout;
	std::vector<IVulkanSlotBinding*> _bindings;
	void InitializeDescriptorSet(VkDescriptorSet dsHandle);
	~VulkanDescriptorSet();
public:
	VulkanDescriptorSet(VulkanDescriptorSetLayout *pLayout);
	VulkanDescriptorSetLayout* GetLayout() const { return _pLayout; }
	VkDescriptorSet GetHandle() const { eassert(_dsHandle != nullptr, "Error trying to get a descriptor set handle that was not allocated yet by its pool");  return _dsHandle; }
	const std::vector<IVulkanSlotBinding*>& GetBindings() { return _bindings; }
	void LoadIfNeeded();
};

