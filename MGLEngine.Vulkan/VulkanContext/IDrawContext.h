#pragma once
#include  "../RenderPipeline/VulkanSemaphore.h"
#include "../Shaders/IRenderContext.h"
class IDrawContext
{
public:
	virtual bool IsWindowResized()=0;
	virtual  VulkanSemaphore GetSemaphore() = 0;
	virtual  IRenderContext* GetRenderContext() = 0;
};

class DrawContext : public IDrawContext
{
public:
	bool WindowResized;
	VulkanSemaphore CurrentSemaphore;
	IRenderContext  *RenderContext;

	DrawContext() {}

	bool  IsWindowResized() override { return WindowResized; }
	
	VulkanSemaphore GetSemaphore() override {
		return CurrentSemaphore;
	}

	IRenderContext * GetRenderContext() override { return RenderContext; }



};