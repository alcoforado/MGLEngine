#include "Triangle2D.h"
#include "MGLEngine.Shared/Utils/JsonParser/mjson.h"


void Triangle2D::WriteTopology(ArraySelect<glm::vec2>& array, Indices& indices)
{
	array[0] = V0;
	array[1] = V1;
	array[2] = V2;
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
}

Triangle2D::Triangle2D()
{
	V0 = { 0,0 };
	V1 = { 0,0 };
	V2 = { 0,0 };


}

Triangle2D::Triangle2D(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2)
{
	V0 = v0;
	V1 = v1;
	V2 = v2;
}

std::string Triangle2D::Serialize()
{
	json j;
	j["P0"]= V0;
	j["P1"]= V1;
	j["P2"]= V2;
	return j.dump();
}

void Triangle2D::Deserialize(std::string str)
{
	json j = json::parse(str);
	V0 = j["P0"];
	V1 = j["P1"];
	V2 = j["P2"];
}


Triangle2D::~Triangle2D()
{
}
