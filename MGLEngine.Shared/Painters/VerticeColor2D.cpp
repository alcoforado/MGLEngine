#include "VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/JsonParser/mjson.h>
std::string VerticeColor2D::Serialize()
{
	json j;
	j["Colors"]=jsonext::SerializeAsColor(Colors);
	return j.dump();
}



void VerticeColor2D::Deserialize(std::string str)
{
	json j = json::parse(str);
	Colors = j["Colors"].get<std::vector<glm::vec3>>();;
}

IShapeHandle* VerticeColor2D::Draw(ICanvas* canvas, ITopology2D* top)
{
	return canvas->GetColor2DShader()->Add(top, this);
}
