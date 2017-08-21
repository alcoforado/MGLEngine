#pragma once
#include "MGLContainer.h"
#include <MGLEngine.Shared/IMGLContainer.h>
#include <MGLEngine.Shared/Window/IWindow.h>
class Window;
class MGLContainer :public  IMGLContainer
{

public:

	MGLContainer()
	{
	}

	virtual IWindow*  CreateWindow();
	


	~MGLContainer()
	{
	}
};

