#include "AppBuilder.h"
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
s_ptr<MGLEngine> AppBuilder::Init()
{
	if (_pEngine == nullptr)
		_pEngine = s_new<MGLEngine>(_windowOptions, _appConfiguration);
	return _pEngine;
}
