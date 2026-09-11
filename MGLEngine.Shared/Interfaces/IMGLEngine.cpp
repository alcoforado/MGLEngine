#include "IMGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>

bool IMGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shadersIndex.find(shaderType) != _shadersIndex.end();
}

void IMGLEngine::SetGlobalBindingTable()
{
	for (auto& ctx : _shaders)
	{
		ctx.BindShapeResources(_pGlobalBindingsTable);
	}
}

IMGLEngine::IMGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig)
	:_gl(*VulkanEngineContainer::GetLibrary(wOptions, appConfig))
{
	
}

IMGLEngine::~IMGLEngine()
{
	delete &_gl;
}

void IMGLEngine::Run()
{
	this->SetGlobalBindingTable();

	_gl.Run(_shaders,*_pGlobalBindingsTable);
}