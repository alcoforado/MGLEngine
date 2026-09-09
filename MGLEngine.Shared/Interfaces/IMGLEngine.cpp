#include "IMGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>


bool IMGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shaders.find(shaderType) != _shaders.end();
}

void IMGLEngine::SetGlobalBindingTable()
{
	for (auto& sh : _shaders)
	{
		auto& ctx = sh.second;
		ctx.BindShapeResources(_pGlobalBindingsTable);
	}
}


