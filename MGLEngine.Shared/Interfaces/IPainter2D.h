#pragma once
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>

class ICanvas;
class IShapeHandle;
class IPainter2D : public ISerializable
{
public:
	virtual IShapeHandle* Draw(ICanvas *canvas,ITopology2D *top) =0;
	
	
};

