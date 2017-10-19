#pragma once
#include <IMGLContainer.h>

ref class UnmanagedFacade
{
public:
	UnmanagedFacade();
	static IMGLContainer* GetContainer();
};

