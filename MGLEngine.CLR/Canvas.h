#pragma once
#include "ShapeHandle.h"

using namespace MGLEngine::Managed::Renders;
using namespace MGLEngine::Managed::Topologies;
using namespace System::Collections::Generic;
using namespace System::Reflection;
class IMGLEngine;
namespace MGLEngineCLR {
	using namespace System;

	ref class Topology2DMapper;
	ref class Window;
	public ref class Canvas
	{
		IMGLEngine *_engine;
		Topology2DMapper^ _mapper;
		static Dictionary<String^, MethodInfo^> ^dictionary = gcnew Dictionary<String^, MethodInfo^>();
	
		Dictionary<String^, MethodInfo^>^ GetReflectionDictionary();
	internal:
		Canvas(IMGLEngine *_engine);
	
	public:
		ShapeHandle^ Render(IMngTopology2D^ topology, CyclicColor2D^ render);
		ShapeHandle^ Render(IMngTopology2D^ topology, IRender2D^ render);
	};

}