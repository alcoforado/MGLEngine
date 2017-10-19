#pragma once


using namespace MGLEngine::Managed::Renders;
using namespace MGLEngine::Managed::Topologies;

public ref class Canvas
{
public:
	Canvas();
	void Render(IMngTopology2D^ topology, CyclicColor2D^ render);
};

