#pragma once
#include "Shaders/IShader.h"
#include "VerticeData/Color2D.h"

class IMGLEngine
{
public:
	virtual IShader<Color2D>* Color2DShader() = 0;
	virtual void Redraw() = 0;

};
