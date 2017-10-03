#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <fstream>
#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include "VulkanSwapChain.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../Shaders/IVulkanRenderContext.h"
#include "../Shaders/ShaderColor2D.h"
#include "IDrawContext.h"
#include <MGLEngine.Shared/Utils/opointer.h>
struct GLFWwindow;




class VulkanContext : public IVulkanRenderContext
{
	//static public
private:
	
private:
	
	ShaderColor2D *_render;
	VulkanInstance _vkInstance;
	OPointer<VulkanLogicalDevice> _vkLogicalDevice;
	OPointer<VulkanSwapChain> _pSwapChain;
	VulkanCommandPool _commandPool;
	VulkanMemoryManager _memoryMngr;
	DrawContext _drawContext;
public:
	VulkanContext(GLFWwindow* window);
	void OnResize(GLFWwindow *window, int newWidth, int newHeight);
	~VulkanContext();
	void Initialize(GLFWwindow* window);
	
	std::vector<VulkanPhysicalDevice> GetPhysicalDevices(VkInstance &inst) const;
	virtual const VulkanSwapChain& GetSwapChain() const override {
		return *_pSwapChain;
	}

	virtual const VulkanLogicalDevice* GetLogicalDevice() const override { return _vkLogicalDevice; }
	void Draw();
	virtual const VulkanCommandPool* GetCommandPool() const override { return &_commandPool; }
	virtual VulkanMemoryManager* GetMemoryManager() override { return &_memoryMngr; }

	ShaderColor2D* GetShaderColor2D() { return _render; }

};

