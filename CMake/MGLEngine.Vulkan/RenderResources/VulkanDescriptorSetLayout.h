#pragma once
#pragma once
#include <MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h>
#include <vector>
#include <string>
class VulkanLogicalDevice;

//DescriptorSetLayout  describe the subset of slots in the shader that a descriptorset has
class VulkanDescriptorSetLayout
{
	friend class VulkanDescriptorSetPool;
	std::string _name;
	VkDescriptorSetLayout _handle;
	const VulkanLogicalDevice *_dev;
	std::vector<IVulkanRenderSlot*> _slots; //All the slots that compose the layout
	;
public:
	VulkanDescriptorSetLayout(const VulkanLogicalDevice* device, std::string name, const std::vector<IVulkanRenderSlot*> &v);
	VkDescriptorSetLayout GetHandle() const { return _handle; }
	~VulkanDescriptorSetLayout();
	std::string GetName() { return _name; }
	const VulkanLogicalDevice* GetVulkanLogicalDevice() const { return _dev; }
	std::vector<IVulkanRenderSlot*> GetSlots() { return _slots; };
};

