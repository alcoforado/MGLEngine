#include "VulkanDescriptorSetPool.h"
#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include "MGLEngine.Vulkan/RenderPipeline/VulkanPipeline.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>

VulkanDescriptorSetPool::VulkanDescriptorSetPool(VulkanLogicalDevice *dev)
{
	_dev = dev;

	_alloc = {};
	_handle = VK_NULL_HANDLE;
}

VulkanDescriptorSetPool::~VulkanDescriptorSetPool()
{
	vkDestroyDescriptorPool(_dev->GetHandle(), _handle, nullptr);
	for (auto ds : _descriptorSets)
	{
		delete ds;
	}
}

VulkanDescriptorSet* VulkanDescriptorSetPool::CreateDescriptorSet(VulkanDescriptorSetLayout *pLayout)
{
	if (IsAllocated())
	{
		throw new Exception("Vulkan Descriptor Pool were already allocated, can't create more VulkanDescriptorSets for this pool");
	}
	
	auto result = new VulkanDescriptorSet(pLayout);
	for (auto slot : pLayout->GetSlots())
	{
		switch (slot->GetVkDescriptorSetLayoutBinding().descriptorType)
		{
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
				_alloc.UniformBuffers++;
				break;
			default:
				throw new Exception("VulkanDescriptorSetPool: Binding type not implemented yet");
		}

	}
	_descriptorSets.push_back(result);
	return result;
}



/*
 *
 */
void VulkanDescriptorSetPool::AllocateDescriptorSets()
{
	if (IsAllocated())
	{
		throw new Exception("Vulkan Descriptor Pool were already allocated, can't call Allocate function again");
	}

	std::vector<VkDescriptorPoolSize> v;
	v.push_back(
		{
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			_alloc.UniformBuffers
		});

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(v.size());
	poolInfo.pPoolSizes = v.data();
	poolInfo.maxSets = static_cast<uint32_t>(_descriptorSets.size());
	VkResult r = vkCreateDescriptorPool(_dev->GetHandle(), &poolInfo, nullptr, &_handle);
	AssertVulkanSuccess(r);

	//For each DescriptorSet already created allocate a VkDescriptorSet for each one of them and set their state as allocated
	//Collect the layouts from the descriptor sets created so far with this pool
	std::vector<VkDescriptorSetLayout> layouts;
	for (auto d: _descriptorSets)
	{
		layouts.push_back(d->GetLayout()->GetHandle());
	}

	//Set the Allocation Structure
	VkDescriptorSetAllocateInfo poolAlloc = {};
	poolAlloc.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	poolAlloc.descriptorPool = _handle;
	poolAlloc.descriptorSetCount = static_cast<uint32_t>(layouts.size());
	poolAlloc.pSetLayouts = layouts.data();

	//Allocate the vector to hold the descriptor sets.
	std::vector<VkDescriptorSet> ds(_descriptorSets.size(), VK_NULL_HANDLE);

	//Allocate
	VkResult result = vkAllocateDescriptorSets(_dev->GetHandle(), &poolAlloc, ds.data());
	AssertVulkanSuccess(result);

	//Distribute the VkDescriptorSets to the VulkanDescriptorSets of the pool
	for (int i=0;i<ds.size();i++)
	{
		_descriptorSets[i]->InitializeDescriptorSet(ds[i]);
	}

}

bool VulkanDescriptorSetPool::IsAllocated()
{
	return _handle != VK_NULL_HANDLE;
}

