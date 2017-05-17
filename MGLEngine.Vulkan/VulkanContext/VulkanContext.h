#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include "VulkanSwapChain.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../Renders/IRenderContext.h"
struct GLFWwindow;




class VulkanContext : public IRenderContext
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
	virtual const VulkanSwapChain& GetSwapChain() const override {
		return _swapChain;
	}

	virtual const VulkanLogicalDevice& GetLogicalDevice() const override { return _vkLogicalDevice; }
};

