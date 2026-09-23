#include "MGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
#include<MGLEngine.Shared/Resources/ImageLoader.h>
MGLEngine::MGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig)
	:_appConfig(appConfig),
	_gl(*VulkanEngineContainer::GetLibrary(wOptions, appConfig))
{

}

MGLEngine::~MGLEngine()
{
	delete& _gl;
}

void MGLEngine::Run()
{
	this->LoadShaders();

	this->LoadResources();
	_gl.Run(_shaders, *_pGlobalBindingsTable);
}

bool MGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shadersIndex.find(shaderType) != _shadersIndex.end();
}

void MGLEngine::LoadShaders()
{
	_pGlobalBindingsTable = s_new<GlobalBindingsTable>();
	for (auto& shader : _shaders)
	{
		shader.DeclareShaderBindings(*_pGlobalBindingsTable);
		shader.BindShapeResources(*_pGlobalBindingsTable);
		shader.glId = _gl.LoadShader(shader, *_pGlobalBindingsTable);
	}
}

void MGLEngine::LoadResources()
{
	for (auto& sampler2D : _pGlobalBindingsTable->GetSampler2DBindings())
	{
		if (sampler2D.glId.Undefined())
		{
			sampler2D.glId = _gl.CreateTextureSampler();
		}
		if (sampler2D.imageFiles.size() == 1)
		{
			sampler2D.imageFiles[0].glId = GetOrCreateCachedResource(sampler2D.imageFiles[0]);
			_gl.AssignResource(sampler2D.glId, sampler2D.imageFiles[0].glId);
		}
	}
}

GLID MGLEngine::GetOrCreateCachedResource(ImageRef& imgRef)
{
	if (_resourcesCache.contains(imgRef.filePath))
	{
		return _resourcesCache[imgRef.filePath];
	}
	else
	{
		ImageLoader imgLoader(_appConfig.ImageRootPath);
		auto s_pImg = imgLoader.LoadAsRGBA(imgRef.filePath);
		auto result = _gl.LoadTexture(*s_pImg);
		_resourcesCache[imgRef.filePath] = result;
		return result;
	}
}



