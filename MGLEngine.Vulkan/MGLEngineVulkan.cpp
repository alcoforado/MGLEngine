#include "MGLEngineVulkan.h"
#include "Window/MWindow.h"
#include <MGLEngine.Vulkan\VulkanContext\VulkanContext.h>
#include <MGLEngine.Shared/Window/IWindow.h>


MGLEngineVulkan::MGLEngineVulkan(IWindow* win)
{
	_window = dynamic_cast<MGL::Window*>(win);
}

MGLEngineVulkan::~MGLEngineVulkan()
{
}

IShader<Color2D>* MGLEngineVulkan::Color2DShader()
{
	return dynamic_cast<IShader<Color2D>*>(_window->GetVulkanContext()->GetShaderColor2D());
}

void MGLEngineVulkan::Redraw()
{
	return  _window->Redraw();
}

