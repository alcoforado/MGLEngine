#pragma once
#include <string>
#include "MGLEngine.Shared/Interfaces/ITopology2D.h"
#include <functional>
#include <map>


class ShapesService
{
private:
	struct Topology2DType
	{
		public:
			std::function<ITopology2D*(void)> Create;
	};
	std::map<std::string, Topology2DType> _topologies2D;




private:
	void registerTopologies();



public:
	ShapesService();
	~ShapesService();

	void CreateShape(std::string jsonShape);
	//void UpdateShape(std::string shape);
	//void DeleteShape(int shapeId);
};

