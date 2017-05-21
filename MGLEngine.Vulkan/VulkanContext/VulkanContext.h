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
#include "../Renders/RenderColor2D.h"
#include "Utils/opointer.h"
struct GLFWwindow;




class VulkanContext : public IRenderContext
{
	//static public
public:
	
private:
	
	RenderColor2D *render;
	VulkanInstance _vkInstance;
	VulkanLogicalDevice _vkLogicalDevice;
	OPointer<VulkanSwapChain> _pSwapChain;
	VulkanCommandPool _commandPool;
public:
	VulkanContext(GLFWwindow* window);
	void OnResize(GLFWwindow* window);
	~VulkanContext();
	void Initialize(GLFWwindow* window);
	
	std::vector<VulkanPhysicalDevice> GetPhysicalDevices(VkInstance &inst) const;
	virtual const VulkanSwapChain& GetSwapChain() const override {
		return *_pSwapChain;
	}

	virtual const VulkanLogicalDevice& GetLogicalDevice() const override { return _vkLogicalDevice; }
	void Draw();
	virtual const VulkanCommandPool* GetCommandPool() const override { return &_commandPool; }
};

