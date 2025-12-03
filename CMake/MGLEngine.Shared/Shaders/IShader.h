#pragma once
#include "IShaderConfiguration.h"
class IShader {
	virtual void Init(IShaderConfiguration& config) = 0;
};