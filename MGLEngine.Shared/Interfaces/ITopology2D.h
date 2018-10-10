#pragma once
#include <glm/detail/type_vec.hpp>
#include "../Utils/Arrays/IArray.h"
#include "../Utils/Arrays/Indices.h"
#include "../Utils/Arrays/ArraySelect.h"
#include "ISerializable.h"


enum TOPOLOGY_TYPE {TRIANGLES,LINES};
class ITopology2D : ISerializable
{
public:
	virtual Index NVertices()=0;
	virtual Index NIndices()=0;
	virtual TOPOLOGY_TYPE GetTopologyType() = 0;

	virtual void WriteTopology(ArraySelect<glm::vec2> &array, Indices& indices) = 0;
	
	ITopology2D();
	~ITopology2D();
};

