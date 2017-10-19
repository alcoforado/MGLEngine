#pragma once
#include <MGLEngine.Shared/IMGLContainer.h>
#include <MGLEngine.Shared/Window/IWindow.h>
#include <MGLEngine.Shared/IMGLEngine.h>
class Window;
class MGLContainer :public  IMGLContainer
{

public:

	MGLContainer()
	{
	}

	virtual IWindow*  CreateWindow();
	virtual IMGLEngine* CreateMGLEngine(IWindow *win);


	~MGLContainer()
	{
	}
};

