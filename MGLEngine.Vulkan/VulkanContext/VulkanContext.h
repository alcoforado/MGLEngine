#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
struct GLFWwindow;




class VulkanContext
{
	//static public
public:
	
private:
	

	VulkanInstance _vkInstance;
	VkDevice _vkLogicalDevice;

	std::vector<VulkanPhysicalDevice> _vkDevices;
	std::vector<VulkanLayerProperties> _vkLayers;
public:
	VulkanContext();
	~VulkanContext();
	void Initialize(GLFWwindow* window);
	
	std::vector<VulkanPhysicalDevice> GetPhysicalDevices(VkInstance &inst) const;
};

