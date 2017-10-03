#pragma once
#include  "../RenderPipeline/VulkanSemaphore.h"
#include "../Shaders/IVulkanRenderContext.h"
class IDrawContext
{
public:
	virtual bool IsWindowResized()=0;
	virtual  VulkanSemaphore* GetSemaphore() = 0;
	virtual  IVulkanRenderContext* GetRenderContext() = 0;
};

class DrawContext : public IDrawContext
{
public:
	bool WindowResized;
	VulkanSemaphore *CurrentSemaphore;
	IVulkanRenderContext  *RenderContext;

	DrawContext() {}

	bool  IsWindowResized() override { return WindowResized; }
	
	VulkanSemaphore* GetSemaphore() override {
		return CurrentSemaphore;
	}

	IVulkanRenderContext * GetRenderContext() override { return RenderContext; }



};