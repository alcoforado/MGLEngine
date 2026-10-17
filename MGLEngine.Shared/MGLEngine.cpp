#include "MGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
#include<MGLEngine.Shared/Resources/ImageLoader.h>
MGLEngine::MGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig)
	:_appConfig(appConfig),
	_gl(*VulkanEngineContainer::GetLibrary(wOptions, appConfig)),
	_resourceManager(_gl,appConfig.AssetsRootPath)
{

}

MGLEngine::~MGLEngine()
{
	delete& _gl;
}

void MGLEngine::Run()
{
	
	this->LoadShaders();

	_gl.Run(_shaders, _resourceManager);
}

bool MGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shadersIndex.find(shaderType) != _shadersIndex.end();
}

void MGLEngine::LoadShaders()
{
	
	for (auto& shader : _shaders)
	{
		_resourceManager.RegisterShaderBindings(shader);
		_resourceManager.RegisterShapeResources(shader);
	}
	_resourceManager.LoadAllResources();
	_gl.LoadShaders(_shaders, _resourceManager);
}






 