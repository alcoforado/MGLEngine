#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>

class IMGLEngine {
	virtual void AddShape(IDrawingObject& shape) =0;

};