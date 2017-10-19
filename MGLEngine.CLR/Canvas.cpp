#include "stdafx.h"
#include "Canvas.h"
#include "Mappers/Topology2DMapper.h"

Canvas::Canvas()
{
}

void Canvas::Render(IMngTopology2D^ topology, CyclicColor2D^ render)
{
	Topology2DMapper ^mapper = gcnew Topology2DMapper();
	mapper->Map(topology);
}
