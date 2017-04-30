#pragma once
#include "Window/IWindow.h"

class IMGLContainer
{
public:

	IMGLContainer()
	{
	}

	virtual IWindow*  CreateWindow() = 0;
	
	~IMGLContainer()
	{
	}
};

