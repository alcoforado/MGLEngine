#pragma once
#include <glm/detail/type_vec.hpp>
#include "../Utils/Arrays/IArray.h"
class ITopology2D
{
public:
	virtual size_t NVertices()=0;
	virtual size_t NIndices()=0;

	virtual void WriteTopology(IArray<glm::vec2> &array)
	{
		
	}

	ITopology2D();
	~ITopology2D();
};

