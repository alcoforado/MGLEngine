#pragma once
#include "MGLContainer.h"
#include <IMGLContainer.h>
#include <Window/IWindow.h>
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

