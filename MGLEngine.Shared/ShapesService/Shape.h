#pragma once
#include "MGLEngine.Shared/Interfaces/ITopology2D.h"
#include "MGLEngine.Shared/Interfaces/IPainter2D.h"

class Shape
{
	int Id;
	ITopology2D *Top2d;
	IPainter2D *Painter;
public:
	Shape(int id,ITopology2D *top2d,IPainter2D *painter);
	~Shape();
};

