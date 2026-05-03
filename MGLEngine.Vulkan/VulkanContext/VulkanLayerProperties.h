#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include<string>


struct VulkanExtension {
	std::string Name;
	uint32_t SpecVersion=0;


};

struct MVulkanLayer {
	std::string Name;
	uint32_t    SpecVersion;
	uint32_t    ImplementationVersion;
	std::string Description;
	std::vector<VulkanExtension> Extensions;

	MVulkanLayer(VkLayerProperties vk,const std::vector<VkExtensionProperties> &extensions) {
		Name = std::string(vk.layerName);
		SpecVersion = vk.specVersion;
		ImplementationVersion = vk.implementationVersion;
		Description = std::string(vk.description);
		for (const auto &ext : extensions) {
			VulkanExtension ve;
			ve.Name = std::string(ext.extensionName);
			ve.SpecVersion = ext.specVersion;
			Extensions.push_back(ve);
		}
	}
	

	
};

