#pragma once
#include  "../RenderPipeline/VulkanSemaphore.h"
#include "../Shaders/IVulkanRenderContext.h"
class IDrawContext
{
public:
	virtual bool IsWindowResized()=0;
	virtual  VulkanSemaphore* GetSwapChainSemaphore() = 0;
	virtual  IVulkanRenderContext* GetRenderContext() = 0;
	virtual int GetFrameIndex() = 0;

};

class DrawContext : public IDrawContext
{
public:
	bool WindowResized;
	VulkanSemaphore *CurrentSemaphore;
	IVulkanRenderContext  *RenderContext;
	int FrameIndex;
	DrawContext() {}

	bool  IsWindowResized() override { return WindowResized; }
	
	VulkanSemaphore* GetSwapChainSemaphore() override {
		return CurrentSemaphore;
	}

	IVulkanRenderContext * GetRenderContext() override { return RenderContext; }

	int GetFrameIndex() override { return FrameIndex; }

};