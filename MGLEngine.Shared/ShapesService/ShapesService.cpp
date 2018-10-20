#include "ShapesService.h"
#include "MGLEngine.Shared/Topologies/Triangle2D.h"
#include "MGLEngine.Shared/Painters/VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/collection_functions.h>

void ShapesService::registerTopologies()
{
	_topologies2D.insert({ "Triangle2D", { []() {return new Triangle2D(); }	} });
	
}

void ShapesService::registerShapes2D()
{
	_shapes2D.insert({ "CyclicColor2D",{[]() {return new VerticeColor2D(); }} });
}


ShapesService::ShapesService()
{
	registerTopologies();
	registerShapes2D();
}


ShapesService::~ShapesService()
{
}

std::string ShapesService::CreateShape(std::string topologyType, std::string renderType)
{
	if (mstd::Does(_topologies2D).Have(topologyType) && mstd::Does(_shapes2D).Have(renderType))
	{
		ITopology2D* top = _topologies2D[topologyType].Create();
		IPainter2D *shape = _shapes2D[renderType].Create();


	}

	return"";
}


