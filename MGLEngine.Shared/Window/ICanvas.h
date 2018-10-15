#pragma once
#include "MGLEngine.Vulkan/Shaders/ShaderColor2D.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual IShader2D<Color2D>* GetColor2DShader() = 0;
};

