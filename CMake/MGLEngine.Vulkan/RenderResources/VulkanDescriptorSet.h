#pragma once
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include "IVulkanSlotBinding.h"
#include <vector>
#include <cassert>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared\Utils\Arrays\IArray.h>

class VulkanLogicalDevice;
class VulkanDescriptorSetPool;
class SlotManager;
class VulkanDescriptorSetLayout;

/*
	A DescriptorSet is a collection (subset) of all the slots of a shader programs, 
	and respectives GPU  memory buffer
	Generally we have one descriptor set for every frame of the swapchain,
*/

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
	IVulkanSlotBinding* GetBinding(IVulkanRenderSlot* pSlot);
	void LoadIfNeeded();

	template<class SlotType>
	void setValue(SlotType* pSlot, const IArray<typename SlotType::ElemData>& data)
	{
		//Get the binding asociated with the slot
		typename SlotType::SlotBinding* pBinding = static_cast<typename SlotType::SlotBinding*>(this->GetBinding(pSlot));
		
		//Update the binding with the data
		pBinding->Update(data);
	}
};

