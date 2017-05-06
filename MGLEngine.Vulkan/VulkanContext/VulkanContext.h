#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
#include "VulkanPhysicalDevice.h"
struct GLFWwindow;




class VulkanContext
{
	//static public
public:
	
	static  std::ofstream *err;
private:
	

	VkInstance _vkInstance;
	VkDevice _vkLogicalDevice;

	std::vector<VulkanPhysicalDevice> _vkDevices;
	std::vector<VulkanLayerProperties> _vkLayers;
public:
	VulkanContext();
	~VulkanContext();
	void AssertVulkanSuccess(VkResult res) const;
	void Initialize(GLFWwindow* window);
	std::vector<VulkanLayerProperties> GetInstanceLayerProperties() const;
	std::vector<VulkanLayerProperties> GetDeviceLayerProperties(VkPhysicalDevice dev) const;
	
	VkDevice CreateLogicalDevice(VulkanPhysicalDevice physicalDevice) const;
	std::string MapVkResultToString(VkResult result) const;
	std::vector<VulkanPhysicalDevice> GetPhysicalDevices(VkInstance &inst) const;
	VkSurfaceKHR GetSurfaceKHR(GLFWwindow* window) const;
};

