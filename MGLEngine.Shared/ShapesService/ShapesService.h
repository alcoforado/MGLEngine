#pragma once
#include <string>
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include <MGLEngine.Shared/Interfaces/IPainter2D.h>
#include <functional>
#include <map>
#include "MGLEngine.Shared/Window/IWindow.h"
#include "ShapeScene.h"


class ShapesService
{
private:
	
	
	struct Topology2DType
	{
		public:
			std::function<ITopology2D*(void)> Create;
	};
	std::map<std::string, Topology2DType> _topologies2D;

	struct Painter2DType
	{
		public:
			std::function<IPainter2D*(void)> Create;
	};
	std::map<std::string, Painter2DType> _painters2d;

	IWindow * _pWindow;

	int _idCount;

	std::map<int, ShapeScene> _shapes;

	
private:	
	void registerTopologies();
	void registerShapes2D();
	void registerShapes3D();
	ShapeScene CreateShape(int shapeId, std::string topologyType, std::string renderType);

public:
	ShapesService(IWindow *pWindow);
	~ShapesService();

	const std::map<std::string, Painter2DType>& GetPainters2D() const { return _painters2d; }
	const std::map<std::string, Topology2DType>& GetShapes2D() const { return _topologies2D; }



	int NewShapeId();
	std::string CreateShape(std::string topologyType,std::string renderType);
	void UpdateShape(int shapeId,std::string shapeJson);
	void DeleteShape(int shapeId);
};

