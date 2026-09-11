#include "MGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>

bool MGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shadersIndex.find(shaderType) != _shadersIndex.end();
}

void MGLEngine::SetGlobalBindingTable()
{
	for (auto& ctx : _shaders)
	{
		ctx.DeclareShaderBindings(*_pGlobalBindingsTable);
		ctx.BindShapeResources(*_pGlobalBindingsTable);
	}
}

MGLEngine::MGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig)
	:_gl(*VulkanEngineContainer::GetLibrary(wOptions, appConfig))
{
	
}

MGLEngine::~MGLEngine()
{
	delete &_gl;
}

void MGLEngine::Run()
{
	this->SetGlobalBindingTable();

	_gl.Run(_shaders,*_pGlobalBindingsTable);
}