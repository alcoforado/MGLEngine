#include "VerticeColor2D.h"
#include <MGLEngine.Shared/Utils/JsonParser/JsonParser.h>
std::string VerticeColor2D::Serialize()
{
	JsonParser j;
//	j.AddMemberAsColor("Colors", Colors);
	return j.dump();
}

void VerticeColor2D::Deserialize(std::string str)
{
	JsonParser j(str);
//	std::vector<glm::vec3> v = j["Colors"];

}
