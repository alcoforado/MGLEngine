#pragma once
#include "../Utils/Arrays/IArray.h"
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include "MGLEngine.Shared/Shaders/IShader2D.h"
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include <MGLEngine.Shared/Window/ICanvas.h>

class IPainter2D : public ISerializable
{
public:
	virtual IShapeHandle* Draw(ICanvas *canvas,ITopology2D *top) =0;
	
	
};

