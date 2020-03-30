#pragma once
#include <MGLEngine.Shared/Window/ICanvas.h>

namespace MGL {
	class Window;
}

class VulkanCanvas : public ICanvas
{
	MGL::Window *_window;
public:
	VulkanCanvas(MGL::Window *window);
	~VulkanCanvas();
	IShader2D<Color2D>* GetColor2DShader() override;
};

