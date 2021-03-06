#pragma once
#include  "../RenderPipeline/VulkanSemaphore.h"
#include "../Shaders/IVulkanRenderContext.h"
#include "MGLEngine.Vulkan/RenderPipeline/VulkanSemaphorePool.h"
#include "MGLEngine.Vulkan/RenderResources/VulkanResourceLoadContext.h"


struct Output
{
	std::vector<VulkanCommandBuffer*> Commands;
};
class IDrawContext
{
public:
	virtual bool IsWindowResized()=0;
	virtual  VulkanSemaphore* GetSwapChainSemaphore() = 0;
	virtual  IVulkanRenderContext* GetRenderContext() = 0;
	virtual IVulkanResourceLoadContext* GetResourceLoadContext() = 0;
	virtual int GetFrameIndex() = 0;
	Output Out;

	
};

class DrawContext : public IDrawContext
{
public:
	bool WindowResized;
	VulkanSemaphore *CurrentSemaphore;
	IVulkanRenderContext  *RenderContext;
	VulkanSemaphorePool *Pool;
	IVulkanResourceLoadContext *ResourceLoadContext;
	int FrameIndex;
	
	DrawContext(){}

	virtual bool  IsWindowResized() override { return WindowResized; }
	
	virtual VulkanSemaphore* GetSwapChainSemaphore() override {
		return CurrentSemaphore;
	}

	virtual IVulkanRenderContext * GetRenderContext() override { return RenderContext; }

	 virtual int GetFrameIndex() override { return FrameIndex; }

	 virtual IVulkanResourceLoadContext* GetResourceLoadContext() override { return ResourceLoadContext; }

	

};