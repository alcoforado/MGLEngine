#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include "VulkanSwapChain.h"
struct GLFWwindow;




class VulkanContext
{
	//static public
public:
	
private:
	

	VulkanInstance _vkInstance;
	VulkanLogicalDevice _vkLogicalDevice;
	VulkanSwapChain _swapChain;


public:
	VulkanContext(GLFWwindow* window);
	~VulkanContext();
	void Initialize(GLFWwindow* window);
	
	std::vector<VulkanPhysicalDevice> GetPhysicalDevices(VkInstance &inst) const;
};

