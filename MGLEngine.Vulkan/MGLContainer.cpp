#include "MGLContainer.h"
#include "Window/MWindow.h"
#include "MGLEngineVulkan.h"

IWindow * MGLContainer::CreateWindow()
{
	return new  MGL::Window();
}

IMGLEngine* MGLContainer::CreateMGLEngine(IWindow* win)
{
	return new MGLEngineVulkan(win);
}
