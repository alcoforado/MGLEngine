#pragma once
#include <MGLEngine.Shared/Shaders/IShader2D.h>
#include<MGLEngine.Shared/VerticeData/Color2D.h>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual IShader2D<Color2D>* GetColor2DShader() = 0;
};

