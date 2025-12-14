#include "VulkanAppBuilder.h"
#include <MGLEngine.Vulkan/VulkanEngine.h>

IMGLEngine& MGL::VulkanAppBuilder::Init()
{
	eassert(!_pEngine, "Init function must be called only once");
	
	_pEngine = std::make_shared<VulkanEngine>(_windowOptions, _vulkanConfiguration);
		
	return *_pEngine;
}