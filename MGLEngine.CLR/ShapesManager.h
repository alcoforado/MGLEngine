#pragma once

#include "Window.h"
#include "Models/RenderType.h"
#include "Models/ShapeType.h"

class ShapesService;




namespace MGLEngineCLR {
	using namespace System;
	using namespace System::Collections::Generic;

	




	public ref class ShapesManager
	{
		ShapesService *_sh;
	public:
		ShapesManager(Window^ w);
		~ShapesManager();
		String^ SaveShape(String^ shapeJson);
		void DeleteShape(String^ shapeId);
		List<RenderType^>^ GetRenderTypes();
		List<ShapeType^>^ GetShapeTypes();
		String^ ReserveShapeId(String^ topologyType);
	};
}