#include "ShapesService.h"
#include "MGLEngine.Shared/Topologies/Triangle2D.h"


void ShapesService::registerTopologies()
{
	_topologies2D.insert({ "Triangle2D", { []() {return new Triangle2D(); }	} });
	
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
