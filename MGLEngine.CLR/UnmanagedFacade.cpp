#include "stdafx.h"
#include "UnmanagedFacade.h"
#include <MGLContainerVulkan.h>

UnmanagedFacade::UnmanagedFacade()
{
}


IMGLContainer* UnmanagedFacade::GetContainer()
{
	return new MGLContainerVulkan();
}
