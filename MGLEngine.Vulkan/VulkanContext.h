#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
struct GLFWwindow;

struct LayerProperties {
	VkLayerProperties layer;
	std::vector<VkExtensionProperties> extensions;
};

struct VulkanPhysicalDeviceInfo {
	VkPhysicalDevice Handler;
	std::vector<VkQueueFamilyProperties> FamilyProperties;
	VkPhysicalDeviceMemoryProperties MemoryProperties;
	VkPhysicalDeviceProperties GraphicProperties;
	std::vector<LayerProperties> LayerProperties;
};

class VulkanContext
{
	//static public
public:
	
	static  std::ofstream *err;
private:
	

	VkInstance _vkInstance;
	std::vector<VulkanPhysicalDeviceInfo> _vkDevices;
	std::vector<LayerProperties> _vkLayers;
public:
	VulkanContext();
	~VulkanContext();
	void AssertVulkanSuccess(VkResult res);
	void Initialize(GLFWwindow* window);
	std::vector<LayerProperties> GetInstanceLayerProperties();
	std::vector<LayerProperties> GetDeviceLayerProperties(VkPhysicalDevice dev);
	

	std::string MapVkResultToString(VkResult result);
	std::vector<VulkanPhysicalDeviceInfo> GetPhysicalDevices(VkInstance &inst);
};

