#pragma once
#include <MGLEngine.Shared\IMGLEngine.h>
#include <MGLEngine.Vulkan/Window/MWindow.h>

class IWindow;

class MGLEngineVulkan : public IMGLEngine
{
	MGL::Window *_window;
public:
	MGLEngineVulkan(IWindow *win);
	virtual ~MGLEngineVulkan();
	virtual IShader<Color2D>* Color2DShader() override;
};

