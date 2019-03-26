#pragma once
#include "MGLEngine.Shared/Interfaces/ITopology2D.h"
#include "MGLEngine.Shared/Interfaces/IPainter2D.h"

class SceneObject 
{
public:
	std::string Id;
	ITopology2D *Top2d;
	IPainter2D *Painter;
	IShapeHandle *Handle;
	std::string TopologyType;
	std::string PainterType;
	std::string Name;
public:
	SceneObject(std::string id,std::string name,ITopology2D *top2d,IPainter2D *painter,IShapeHandle *handle,std::string topType, std::string pntType);
	SceneObject(){}
	~SceneObject();
	std::string Serialize();
};

