#include "VulkanAppBuilder.h"
#include <MGLEngine.Vulkan/VulkanEngine.h>

std::shared_ptr<IMGLEngine> MGL::VulkanAppBuilder::Init()
{
	return std::make_shared<VulkanEngine>(_windowOptions, _vulkanConfiguration);
}