#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
struct GLFWwindow;

struct InstanceLayer {
	VkLayerProperties layer;
	std::vector<VkExtensionProperties> extensions;
};

struct VulkanPhysicalDeviceInfo {
	VkPhysicalDevice Handler;
	VkQueueFamilyProperties FamilyProperties;
	VkPhysicalDeviceMemoryProperties MemoryProperties;
	VkPhysicalDeviceProperties GraphicProperties;
};

class VulkanContext
{
	//static public
public:
	
	static  std::ofstream *err;
private:
	

	VkInstance _vkInstance;
	std::vector<VulkanPhysicalDeviceInfo> _vkDevices;
	std::vector<VkPhysicalDevice> _vkDevices;
	std::vector<InstanceLayer> _vkLayers;
public:
	VulkanContext();
	~VulkanContext();
	void AssertVulkanSuccess(VkResult res);
	void Initialize(GLFWwindow* window);
	std::vector<InstanceLayer> GetLayerProperties();
	std::string MapVkResultToString(VkResult result);
	std::vector<VkPhysicalDevice> GetPhysicalDevices(VkInstance &inst);
};

