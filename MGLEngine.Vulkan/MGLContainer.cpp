#include "MGLContainer.h"
#include "Window/MWindow.h"
IWindow * MGLContainer::CreateWindow()
{
	return new  MGL::Window();
}
