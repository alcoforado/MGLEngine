#include "ShapesService.h"
#include "MGLEngine.Shared/Topologies/Triangle2D.h"
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


SceneObject* ShapesService::CreateShape(std::string shapeId,std::string topologyType, std::string renderType) 
{
	if (mstd::Does(_topologies2D).Have(topologyType) && mstd::Does(_painters2d).Have(renderType))
	{
		ITopology2D* top = _topologies2D[topologyType].Create();
		IPainter2D *painter = _painters2d[renderType].Create();
		IShapeHandle *handler = painter->RegisterInShader(_pWindow->GetCanvas(), top);
		SceneObject sceneObj(shapeId,shapeId, top, painter, handler, topologyType, renderType);
		_shapes[sceneObj.Id] = sceneObj;
		return &(_shapes[sceneObj.Id]);
	}
	throw new Exception("Not Implemented");
}



std::string ShapesService::SaveShape(std::string shapeJson)
{
	json j = json::parse(shapeJson);
	if (j.value("Id", "") == "" || j["Id"].is_null()) //no id
	{
	
		SceneObject* shape = this->CreateShape(_nameGen.GenerateName(j["TopologyType"]),j["TopologyType"], j["PainterType"]);
		
		//Set name
		std::string name = j.value("Name","");
		if (name != "")
		{
			shape->Name=name;
		}
		return shape->Serialize();
	}
	else
	{
		int id = j["Id"];
		return shapeJson;
	}
	return std::string();
}

SceneObject* ShapesService::UpdateShape(std::string shapeJson)
{
	json j = json::parse(shapeJson);
	std::string shapeId = j["Id"];
	SceneObject sh = _shapes[shapeId];
	DeleteShape(shapeId);
	SceneObject* newShape = CreateShape(shapeId, j["TopologyType"], j["PainterType"]);
	newShape->Top2d->Deserialize(j["Topology"].dump());
	newShape->Painter->Deserialize(j["Painter"].dump());
	newShape->Handle=newShape->Painter->RegisterInShader(_pWindow->GetCanvas(), newShape->Top2d);
	return newShape;
}





void ShapesService::DeleteShape(std::string shapeId)
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





