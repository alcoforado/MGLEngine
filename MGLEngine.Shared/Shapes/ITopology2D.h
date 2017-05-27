#pragma once
#include <glm/detail/type_vec.hpp>
#include "../Utils/Arrays/IArray.h"
#include "../Utils/Arrays/ArraySelect.h"

class ITopology2D
{
public:
	virtual size_t NVertices()=0;
	virtual size_t NIndices()=0;

	virtual void WriteTopology(ArraySelect<glm::vec2> &array, IArray<int> &indices) = 0;
	
	ITopology2D(){}
	~ITopology2D(){}
};

