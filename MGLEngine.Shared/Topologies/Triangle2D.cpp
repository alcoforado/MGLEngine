#include "Triangle2D.h"


void Triangle2D::WriteTopology(ArraySelect<glm::vec2>& array, Indices& indices)
{
	array[0] = V0;
	array[1] = V1;
	array[2] = V2;
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
}

inline Triangle2D::Triangle2D(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2)
{
	V0 = v0;
	V1 = v1;
	V2 = v2;
}


Triangle2D::~Triangle2D()
{
}
