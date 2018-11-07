#pragma once

#include "Window.h"
#include "Models/RenderType.h"
#include "Models/ShapeType.h"

class ShapesService;




namespace MGLEngineCLR {
	using namespace System;
	using namespace System::Collections::Generic;

	




	ref class ShapesManager
	{
		ShapesService *_sh;
	public:
		ShapesManager(Window^ w);
		~ShapesManager();
		String^ CreateShape(String^ topologyType, String^ renderType);
		void UpdateShape(int shapeId, String^ shapeJson);
		void DeleteShape(int shapeId);
		List<RenderType^>^ GetRenderTypes();
		List<ShapeType^>^ GetShapeTypes();
	};
}