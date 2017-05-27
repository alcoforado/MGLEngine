#pragma once
#include "../Utils/Arrays/IArray.h"

template<class VerticeData>
class IShape2D
{
public:
	virtual size_t NVertices() = 0;
	virtual size_t NIndices() = 0;
	virtual void Write(IArray<VerticeData> &array) = 0;
	
};

