#include "stdafx.h"
#include "UnmanagedFacade.h"
#include <MGLContainer.h>

UnmanagedFacade::UnmanagedFacade()
{
}


IMGLContainer* UnmanagedFacade::GetContainer()
{
	return new MGLContainer();
}
