#include "AppBuilder.h"
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
IMGLEngine& AppBuilder::Init()
{
	if (_pEngine == nullptr)
		_pEngine = s_new<IMGLEngine>(_windowOptions, _appConfiguration);
	return *_pEngine;
}
