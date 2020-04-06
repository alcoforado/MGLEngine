#pragma once

#include <MGLEngine.Shared/Utils/pointers.h>
#include <list>
#include <MGLEngine.Vulkan\DrawTree\IVulkanResourceLoader.h>
#include <MGLEngine.Vulkan\DrawTree\VulkanResourceLoader.h>

class VulkanInternalData
{
public:
	std::list<s_ptr<IVulkanResourceLoader>>  resourceLoaders;
	
	template<class SlotType>
	ResourceLoaderAccessor<typename SlotType::ElemData> AddResourceLoaderPerFrame(SlotType& pSlot, std::vector<VulkanDescriptorSet*> &v)
	{
		ResourceLoaderPerFrame<SlotType> *r=new ResourceLoaderPerFrame<SlotType>(&pSlot, v);
		resourceLoaders.push_back(s_ptr<IVulkanResourceLoader>(r));
		return r->GetAccessor();

	}
};
