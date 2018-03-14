#include "VulkanDescriptorSetPool.h"
#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
VulkanDescriptorSetPool::VulkanDescriptorSetPool(VulkanLogicalDevice *dev,PoolAllocation alloc)
{
	std::vector<VkDescriptorPoolSize> v;
	_dev = dev;
	_alloc = alloc;
	v.push_back(
		{
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			alloc.UniformBuffers
		});
	
	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(v.size());
	poolInfo.pPoolSizes = v.data();
	
	VkResult r = vkCreateDescriptorPool(_dev->GetHandle(), &poolInfo, nullptr,&_handle);

}

VulkanDescriptorSetPool::~VulkanDescriptorSetPool()
{

}
