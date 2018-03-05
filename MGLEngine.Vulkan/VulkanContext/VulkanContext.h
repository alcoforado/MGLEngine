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
	struct PerFrameData
	{
	
		std::vector<VulkanSemaphore*> WaitSemaphoresToPresent;
		VulkanFence *fence;
	};


	ShaderColor2D *_render;
	VulkanInstance _vkInstance;
	OPointer<VulkanLogicalDevice> _vkLogicalDevice;
	OPointer<VulkanSwapChain> _pSwapChain;
	VulkanMemoryManager _memoryMngr;
	DrawContext _drawContext;
	std::vector<PerFrameData> _framesData;
	std::vector<IVulkanShader*> _shaders;
public:
	VulkanContext(GLFWwindow* window);
	void OnResize(GLFWwindow *window, int newWidth, int newHeight);
	~VulkanContext();
	void Initialize(GLFWwindow* window);
	
	std::vector<VulkanPhysicalDevice> GetPhysicalDevices(VkInstance &inst) const;
	virtual const VulkanSwapChain& GetSwapChain() const override {
		return *_pSwapChain;
	}

	virtual VulkanLogicalDevice* GetLogicalDevice() const override { return _vkLogicalDevice; }
	
	void Draw();

	virtual VulkanMemoryManager* GetMemoryManager() override { return &_memoryMngr; }

	ShaderColor2D* GetShaderColor2D() { return _render; }

};

