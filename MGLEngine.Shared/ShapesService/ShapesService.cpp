#include "ShapesService.h"
#include "MGLEngine.Shared/Topologies/Triangle2D.h"
#include "MGLEngine.Shared/Painters/VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/collection_functions.h>
#include "ShapeScene.h"
#include "MGLEngine.Shared/Utils/JsonParser/mjson.h"
#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Shared/Interfaces/IShapeHandle.h>

void ShapesService::registerTopologies()
{
	_topologies2D.insert({ "Triangle2D", { []() {return new Triangle2D(); }	} });
	
}

void ShapesService::registerPainters2D()
{
	_painters2d.insert({ "CyclicColor2D",{[]() {return new VerticeColor2D(); }} });
}


ShapesService::ShapesService(IWindow *pWindow)
{
	registerTopologies();
	registerPainters2D();
	_pWindow = pWindow;
}


ShapesService::~ShapesService()
{
}

int ShapesService::NewShapeId()
{
	return _idCount++;
}


SceneObject ShapesService::CreateShape(int shapeId,std::string topologyType, std::string renderType)
{
	if (mstd::Does(_topologies2D).Have(topologyType) && mstd::Does(_painters2d).Have(renderType))
	{
		ITopology2D* top = _topologies2D[topologyType].Create();
		IPainter2D *painter = _painters2d[renderType].Create();
		IShapeHandle *handler = painter->Draw(_pWindow->GetCanvas(), top);
		SceneObject sceneObj(shapeId, top, painter, handler, topologyType, renderType);
		_shapes[sceneObj.Id] = sceneObj;
		return sceneObj;
	}
	throw new Exception("Not Implemented");
}

std::string ShapesService::CreateShape(std::string topologyType, std::string renderType)
{
	return CreateShape(NewShapeId(), topologyType, renderType).Serialize();
	
	
}

void ShapesService::UpdateShape(int shapeId, std::string shapeJson)
{
	json j = json::parse(shapeJson);
	SceneObject sh = _shapes[shapeId];
	DeleteShape(shapeId);
	SceneObject newShape = CreateShape(shapeId, j["TopologyType"], j["PainterType"]);
	newShape.Top2d->Deserialize(j["Topology"].dump());
	newShape.Painter->Deserialize(j["Painter"].dump());
	newShape.Handle=newShape.Painter->Draw(_pWindow->GetCanvas(), newShape.Top2d);


	
}

void ShapesService::DeleteShape(int shapeId)
{
	if (mstd::Does(_shapes).Have(shapeId))
	{
		if (_shapes[shapeId].Handle)
			_shapes[shapeId].Handle->Delete();
		_shapes.erase(shapeId);
	}
	else
		throw new Exception("Shape does not exist");
}





