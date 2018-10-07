#pragma once
#include "../Utils/Arrays/ArraySelect.h"
#include <glm/detail/type_vec.hpp>

class ITopology3D
{
public:
	virtual size_t NVertices() = 0;
	virtual size_t NIndices() = 0;

	virtual void WriteVertices(ArraySelect<glm::vec3> &array, IArray<int> &indices) = 0;

	ITopology3D();
	~ITopology3D();
};

