#include "ShapeScene.h"
#include <MGLEngine.Shared/Utils/JsonParser/mjson.h>




SceneObject::SceneObject(int id, std::string name, ITopology2D* top2d, IPainter2D* painter, IShapeHandle *handle,  std::string topType, std::string pntType)
{
	Id = id;
	Top2d = top2d;
	Painter = painter;
	Handle = handle;
	TopologyType = topType;
	PainterType = pntType;
	Name = name;
	
}

SceneObject::~SceneObject()
{
}

std::string SceneObject::Serialize()
{
	json j;

	j["Id"] = Id;
	j["TopologyType"] = TopologyType;
	j["PainterType"] = PainterType;
	j["Topology"] = json::parse(Top2d->Serialize());
	j["Painter"] = json::parse(Painter->Serialize());
	return j.dump();

}





