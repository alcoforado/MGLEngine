#include "ShapesService.h"
#include "MGLEngine.Shared/Topologies/Triangle2D.h"
#include "MGLEngine.Shared/Painters/VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/collection_functions.h>
#include "ShapeScene.h"

void ShapesService::registerTopologies()
{
	_topologies2D.insert({ "Triangle2D", { []() {return new Triangle2D(); }	} });
	
}

void ShapesService::registerShapes2D()
{
	_painters2d.insert({ "CyclicColor2D",{[]() {return new VerticeColor2D(); }} });
}


ShapesService::ShapesService(IWindow *pWindow)
{
	registerTopologies();
	registerShapes2D();
	_pWindow = pWindow;
}


ShapesService::~ShapesService()
{
}

int ShapesService::NewShapeId()
{
	return _idCount++;
}

std::string ShapesService::CreateShape(std::string topologyType, std::string renderType)
{
	if (mstd::Does(_topologies2D).Have(topologyType) && mstd::Does(_painters2d).Have(renderType))
	{
		ITopology2D* top = _topologies2D[topologyType].Create();
		IPainter2D *painter = _painters2d[renderType].Create();
		IShapeHandle *handler = painter->Draw(_pWindow->GetCanvas(), top);
		ShapeScene sceneObj(NewShapeId(), top, painter, handler,topologyType,renderType);
		_shapes[sceneObj.Id] = sceneObj;
		return sceneObj.Serialize();
	}
	throw new Exception("Not Implemented");
}


