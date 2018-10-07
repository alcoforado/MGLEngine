#pragma once
#include "../Utils/Arrays/IArray.h"
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include "MGLEngine.Shared/Shaders/IShader.h"
class IDrawContext;
class ITopology2D;
class ICanvas;
class IShape2D : ISerializable
{
public:
	virtual IShapeHandle* Draw(ICanvas *canvas,ITopology2D *top) =0;
	
	
};

