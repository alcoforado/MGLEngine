#pragma once
#include "MGLEngine.Shared/Interfaces/ITopology2D.h"
#include "MGLEngine.Shared/Interfaces/IPainter2D.h"

class ShapeScene 
{
public:
	int Id;
	ITopology2D *Top2d;
	IPainter2D *Painter;
	IShapeHandle *Handle;
	std::string TopologyType;
	std::string PainterType;
public:
	ShapeScene(int id,ITopology2D *top2d,IPainter2D *painter,IShapeHandle *handle,std::string topType, std::string pntType);
	ShapeScene(){}
	~ShapeScene();
	std::string Serialize();
};

