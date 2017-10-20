#include "stdafx.h"
#include "Window.h"
#include "Canvas.h"
#include "Mappers/Topology2DMapper.h"
#include <MGLEngine.Shared\Renders\CyclicColor.h>
#include <MGLEngine.Shared\VerticeData\Color2D.h>


namespace MGLEngineCLR {
	Canvas::Canvas(IMGLEngine *engine)
	{
		_mapper = gcnew MGLEngineCLR::Topology2DMapper();
		_engine = engine;
	}

	void Canvas::Render(IMngTopology2D^ topology, CyclicColor2D^ render)
	{
		ITopology2D* pTop = _mapper->Map(topology);
		auto colors = _mapper->MapList<GlmNet::vec3,glm::vec3>(render->Colors);
		auto pRender = new CyclicColor<Color2D>(colors);
		_engine->Color2DShader()->Add(pTop, pRender);
	}
}