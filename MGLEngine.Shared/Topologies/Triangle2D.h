#pragma once
#include <glm/detail/type_vec2.hpp>
#include "../Utils/Arrays/Indices.h"
#include "../Shapes/ITopology2D.h"

class Triangle2D : public ITopology2D
{
public:
	virtual Index NVertices() override{
		return 3;
	};
	virtual Index NIndices() override  {
		return 3;
	}
	virtual TOPOLOGY_TYPE GetTopologyType()
	{
		return TOPOLOGY_TYPE::TRIANGLES;
	}


	virtual void WriteTopology(ArraySelect<glm::vec2>& array, Indices& indices) override;

	glm::vec2 V0, V1, V2;


	Triangle2D(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2);



	~Triangle2D();
};


