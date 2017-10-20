// This is the main DLL file.

#include "stdafx.h"

#include "Window.h"
#include "Canvas.h"
#include "Mappers\Topology2DMapper.h"
#include <MGLEngine.Shared\IMGLEngine.h>
namespace MGLEngineCLR {

	Window::Window()
	{
		_window = UnmanagedFacade::GetContainer()->CreateWindow();
		_engine = UnmanagedFacade::GetContainer()->CreateMGLEngine(_window);
		_canvas = gcnew Canvas(_engine);
	}


}