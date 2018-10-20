#pragma once
#include <string>
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include <MGLEngine.Shared/Interfaces/IPainter2D.h>
#include <functional>
#include <map>
#include "MGLEngine.Shared/Window/IWindow.h"


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
			std::function<IPainter2D*(void)> Create;
	};
	std::map<std::string, Shape2DType> _shapes2D;

private:
	IWindow * _pWindow;
	
	
	void registerTopologies();
	void registerShapes2D();
	void registerShapes3D();


public:
	ShapesService(IWindow *pWindow);
	~ShapesService();

	

	std::string CreateShape(std::string topologyType,std::string renderType);
	void UpdateShape(int shapeId,std::string top,std::string painter);
	void DeleteShape(int shapeId);
};

