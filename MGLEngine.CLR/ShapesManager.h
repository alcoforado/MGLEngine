#pragma once

#include "Window.h"


class ShapesService;

namespace MGLEngineCLR {
	using namespace System;
	ref class ShapesManager
	{
		ShapesService *_sh;
	public:
		ShapesManager(Window^ w);
		~ShapesManager();
		String^ CreateShape(String^ topologyType, String^ renderType);
		void UpdateShape(int shapeId, String^ shapeJson);
		void DeleteShape(int shapeId);
	};
}