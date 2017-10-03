#include "MGLEngineVulkan.h"

#include <MGLEngine.Vulkan\VulkanContext\VulkanContext.h>



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
