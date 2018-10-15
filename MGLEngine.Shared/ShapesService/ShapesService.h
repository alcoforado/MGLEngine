#pragma once
#include <string>
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include <MGLEngine.Shared/Interfaces/IShape2D.h>
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

	struct Shape2DType
	{
		public:
			std::function<IShape2D*(void)> Create;
	};
	std::map<std::string, Shape2DType> _shapes2D;

private:
	void registerTopologies();
	void registerShapes2D();
	void registerShapes3D();


public:
	ShapesService();
	~ShapesService();

	std::string CreateShape(std::string topologyType,std::string renderType);
	void UpdateShape(int shapeId,std::string top,std::string painter);
	void DeleteShape(int shapeId);
};

