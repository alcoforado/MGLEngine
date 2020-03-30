#include "VulkanCanvas.h"
#include <MGLEngine.Vulkan/Window/MWindow.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanContext.h>
VulkanCanvas::VulkanCanvas(MGL::Window* win)
{
	_window = win;
}

VulkanCanvas::~VulkanCanvas()
{
}

IShader2D<Color2D>* VulkanCanvas::GetColor2DShader()
{
	return dynamic_cast<IShader2D<Color2D>*>(_window->GetVulkanContext()->GetShaderColor2D());
}

