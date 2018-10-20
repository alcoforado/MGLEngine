#include "VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/JsonParser/JsonParser.h>
std::string VerticeColor2D::Serialize()
{
	JsonParser j;
	j["Colors"]=JsonParser::SerializeAsColor(Colors);
	return j.dump();
}



void VerticeColor2D::Deserialize(std::string str)
{
	JsonParser j(str);
	Colors=j["Colors"];
}

IShapeHandle* VerticeColor2D::Draw(ICanvas* canvas, ITopology2D* top)
{
	return canvas->GetColor2DShader()->Add(top, this);
}
