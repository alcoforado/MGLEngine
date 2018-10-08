#include "VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/JsonParser/JsonParser.h>
std::string VerticeColor2D::Serialize()
{
	JsonParser j;
	j.AddMember("Colors", Colors);
	return j.dump();
}
