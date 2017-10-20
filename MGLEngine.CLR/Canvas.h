#pragma once


using namespace MGLEngine::Managed::Renders;
using namespace MGLEngine::Managed::Topologies;

class IMGLEngine;
namespace MGLEngineCLR {
	ref class Topology2DMapper;
	ref class Window;
	public ref class Canvas
	{
		IMGLEngine *_engine;
		Topology2DMapper^ _mapper;
	
	internal:
		Canvas(IMGLEngine *_engine);
	
	public:
		void Render(IMngTopology2D^ topology, CyclicColor2D^ render);
	};

}