#include "MGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
#include<MGLEngine.Shared/Resources/ImageLoader.h>
#include <MGLEngine.Shared/Window/MWindow.h>
MGLEngine::MGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig)
	:_appConfig(appConfig),
	_pWindow(s_new<MWindow>(wOptions)),
	_gl(*VulkanEngineContainer::GetLibrary(_pWindow, appConfig)),
	_resourceManager(_gl,appConfig.AssetsRootPath)
{
	std::cout << "Use Count " <<  _pWindow.use_count() << std::endl;
	_pMGLContainer = s_new<MGLContainer>(&(*_pWindow), &_resourceManager);
}

MGLEngine::~MGLEngine()
{
	std::cout << "Use Count " << _pWindow.use_count() << std::endl;
	delete &_gl;
	std::cout << "Use Count " << _pWindow.use_count() << std::endl;
}

void MGLEngine::Run()
{
	
	this->LoadShaders();

	_gl.Run(_shaders, *_pMGLContainer);
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
	_gl.LoadShaders(_shaders, *_pMGLContainer);
}






 