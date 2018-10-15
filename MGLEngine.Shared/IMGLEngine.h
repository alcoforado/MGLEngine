#pragma once
#include "Shaders/IShader2D.h"
#include "VerticeData/Color2D.h"

class IMGLEngine
{
public:
	virtual IShader2D<Color2D>* Color2DShader() = 0;
	virtual void Redraw() = 0;

};
