#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
struct GLFWwindow;

struct InstanceLayer {
	VkLayerProperties layer;
	std::vector<VkExtensionProperties> extensions;
};

class VulkanContext
{

private:
	void AssertVulkanSuccess(VkResult res);
	
	
	VkInstance _vkInstance;
	std::vector<VkPhysicalDevice> _vkDevices;
	std::vector<InstanceLayer> _vkLayers;
public:
	VulkanContext();
	~VulkanContext();
	void Initialize(GLFWwindow* window);
	std::vector<InstanceLayer> GetLayerProperties();
	std::string MapVkResultToString(VkResult result);
	std::vector<VkPhysicalDevice> GetPhysicalDevices(VkInstance &inst);
};

