#include "ShapesService.h"
#include "MGLEngine.Shared/Topologies/Triangle2D.h"
#include "MGLEngine.Shared/Painters/VerticeColor2D.h"


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
}


ShapesService::~ShapesService()
{
}

void ShapesService::CreateShape(std::string jsonShape)
{


}
