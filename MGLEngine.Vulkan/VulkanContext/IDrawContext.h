#pragma once
#include  "../RenderPipeline/VulkanSemaphore.h"
#include "../Shaders/IRenderContext.h"
class IDrawContext
{
public:
	virtual bool WindowResized()=0;
	virtual  VulkanSemaphore GetSemaphore() = 0;
	virtual  IRenderContext* GetRenderContext() = 0;
};

class DrawContext : public IDrawContext
{
public:
	bool WindowResized;
	VulkanSemaphore CurrentSemaphore;
	IRenderContext * RenderContext;

	bool  WindowResized() override { return WindowResized; }
	
	VulkanSemaphore GetSemaphore() override {
		return CurrentSemaphore;
	}

	IRenderContext * GetRenderContext() override { return RenderContext; }



};