#pragma once
#include  "../RenderPipeline/VulkanSemaphore.h"
#include "../Shaders/IVulkanRenderContext.h"
#include "MGLEngine.Vulkan/RenderPipeline/VulkanSemaphorePool.h"


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
	virtual int GetFrameIndex() = 0;
	virtual size_t GetFrameSize() = 0;
	Output Out;

	
};

class DrawContext : public IDrawContext
{
public:
	bool WindowResized;
	VulkanSemaphore *CurrentSemaphore;
	IVulkanRenderContext  *RenderContext;
	VulkanSemaphorePool *Pool;
	int FrameIndex;
	
	DrawContext(){}

	virtual bool  IsWindowResized() override { return WindowResized; }
	
	virtual VulkanSemaphore* GetSwapChainSemaphore() override {
		return CurrentSemaphore;
	}

	virtual IVulkanRenderContext * GetRenderContext() override { return RenderContext; }

	 virtual int GetFrameIndex() override { return FrameIndex; }

	 virtual size_t GetFrameSize() override {
		 return RenderContext->GetSwapChain()->GetImageViews().size();
	 }
	

};