#pragma once
#include <MGLEngine.Shared/IMGLContainer.h>
#include <MGLEngine.Shared/Window/IWindow.h>
#include <MGLEngine.Shared/IMGLEngine.h>
class Window;
class MGLContainerVulkan :public  IMGLContainer
{

public:

	MGLContainerVulkan()
	{
	}

	virtual IWindow*  CreateWindow();
	virtual IMGLEngine* CreateMGLEngine(IWindow *win);


	~MGLContainerVulkan()
	{
	}
};

