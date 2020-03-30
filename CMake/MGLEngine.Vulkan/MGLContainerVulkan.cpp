#include "MGLContainerVulkan.h"
#include "Window/MWindow.h"
#include "MGLEngineVulkan.h"

IWindow * MGLContainerVulkan::CreateWindow()
{
	return new  MGL::Window();
}

IMGLEngine* MGLContainerVulkan::CreateMGLEngine(IWindow* win)
{
	return new MGLEngineVulkan(win);
}
