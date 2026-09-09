#pragma once
#include <MGLEngine.Shared/Shaders/ShaderConfiguration.h>
class IShader {
	public:
		virtual void Init(ShaderConfiguration& config) = 0;
};