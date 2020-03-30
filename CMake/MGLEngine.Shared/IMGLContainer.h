#pragma once
#include "Window/IWindow.h"
#include <MGLEngine.Shared\IMGLEngine.h>

class ShapesService;
class IMGLContainer
{
public:

	IMGLContainer()
	{
	}

	virtual IWindow*  CreateWindow() = 0;
	virtual IMGLEngine* CreateMGLEngine(IWindow* window) = 0;
	
	~IMGLContainer()
	{
	}
};

