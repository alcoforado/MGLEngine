#pragma once
#include "IShaderConfiguration.h"
class IShader {
	public:
		virtual void Init(IShaderConfiguration& config) = 0;
};