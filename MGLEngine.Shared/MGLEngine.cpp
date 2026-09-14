#include "MGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
#include<MGLEngine.Shared/ResourceLoaders/ImageLoader.h>
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
	this->SetGlobalBindingTable();
	this->LoadResources();
	_gl.Run(_shaders, *_pGlobalBindingsTable);
}

bool MGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shadersIndex.find(shaderType) != _shadersIndex.end();
}

void MGLEngine::SetGlobalBindingTable()
{
	_pGlobalBindingsTable = s_new<GlobalBindingsTable>();
	for (auto& ctx : _shaders)
	{
		ctx.DeclareShaderBindings(*_pGlobalBindingsTable);
		ctx.BindShapeResources(*_pGlobalBindingsTable);
	}
}

void MGLEngine::LoadResources()
{
	ImageLoader imgLoader(_appConfig.ImageRootPath);
	for (auto& sampler2D : _pGlobalBindingsTable->GetSampler2DBindings())
	{
		if (sampler2D.imageFiles.size() == 1)
		{
			auto img=imgLoader.LoadAsRGBA(sampler2D.imageFiles[0].filePath);
			sampler2D.imageFiles[0].glId = _gl.LoadTexture(*img);

		}
	}
}



