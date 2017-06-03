#pragma once
#include <glm/detail/type_vec2.hpp>
#include "../Shapes/ITopology2D.h"

class Triangle2D : public ITopology2D
{
public:
	virtual size_t NVertices() {
		return 3;
	};
	virtual size_t NIndices() {
		return 3;
	}
	virtual void WriteTopology(ArraySelect<glm::vec2> &array, IArray<int> &indices)
	{
		array[0] = V0;
		array[1] = V1;
		array[2] = V2;
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

	}

	glm::vec2 V0, V1, V2;


	Triangle2D(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2)
	{
		V0 = v0;
		V1 = v1;
		V2 = v2;
	}

	~Triangle2D();
};

