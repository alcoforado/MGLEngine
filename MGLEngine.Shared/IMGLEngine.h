#pragma once
#include "Shaders/IShader.h"
#include "MGLEngine.Vulkan/Shaders/ShaderColor2D.h"

class IMGLEngine
{
public:
	virtual IShader<Color2D>* Color2DShader() = 0;
	

};
