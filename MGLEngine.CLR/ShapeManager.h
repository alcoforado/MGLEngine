#pragma once
#include "Models/Renders/Renders2D.h"
#include "Models/Topologies/IMngTopology2D.h"
#include "Models/Renders/IMngRender.h"

using namespace MGLEngineCLR::Models::Topologies;
using namespace MGLEngineCLR::Models::Renders;

public ref class ShapeManager
{
public:
	ShapeManager();
	~ShapeManager();

	void AddShape(Object^ topology, IMngRender^ render)
	{
		

	}

};

