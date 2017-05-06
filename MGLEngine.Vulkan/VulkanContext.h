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
	std::vector<VkQueueFamilyProperties> QueueFamilyProperties;
	VkPhysicalDeviceFeatures Features;
	VkPhysicalDeviceMemoryProperties MemoryProperties;
	VkPhysicalDeviceProperties GraphicProperties;
	std::vector<LayerProperties> LayerProperties;

	std::vector<VkQueueFamilyProperties> FindQueuesWithType(VkFlags flags)
	{
		std::vector<VkQueueFamilyProperties> result;
		for (int i = 0; i < QueueFamilyProperties.size(); i++)
		{
			if (QueueFamilyProperties[i].queueFlags & flags)
			{
				result.push_back(QueueFamilyProperties[i]);
			}
		}
		return result;
	}

	uint32_t FindQueueFamilyIndexWithType(VkFlags flags)
	{
		for (int i = 0; i < QueueFamilyProperties.size(); i++)
		{
			if (QueueFamilyProperties[i].queueFlags & flags)
			{
				return i;
			}
		}
		return -1;
	}

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

