#include "MWindow.h"
#include <MGLEngine.Shared/Utils/Exception.h>
#include <cassert>
#include <glfw/glfw3.h>
#include <MGLEngine.Shared/Window/IWindowEventHandler.h>
bool MWindow::isGLFWInitialized = false;


void window_size_callback(GLFWwindow* window, int width, int height)
{
	auto This = static_cast<MWindow*>(glfwGetWindowUserPointer(window));
	
	This->OnResize(width, height);

}


void MWindow::window_mouse_move_callback(GLFWwindow* window, double x, double y)
{
	MWindow *w = static_cast<MWindow*>(glfwGetWindowUserPointer(window));
	for(auto it: w->_handlers)
	{
		it->OnMouseMove(x, y);
	}
}

MWindow::WindowSize MWindow::Size() {
	MWindow::WindowSize sz;
	glfwGetFramebufferSize(_window, &(sz.width), &(sz.height));
	return sz;
}

MWindow::MWindow(const WindowOptions &options)
{
	_width = options.Width;
	_height = options.Height;
	_window = NULL;
	_isEasyRun = false;
	if (!this->isGLFWInitialized)
	{
		int result = glfwInit();
		if (result == 0)
		{
			throw new Exception("Could not initialize GLFW Window");
		}
		isGLFWInitialized = true;

	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	_window = glfwCreateWindow(_width, _height, options.Title.c_str(), NULL, NULL);
	glfwSetWindowUserPointer(_window, this);
	if (!_window)
	{
		throw new Exception("Create Window failed");
	}

	//Register resize event
	glfwSetWindowSizeCallback(_window, window_size_callback);

	//Register mouse move event
	glfwSetCursorPosCallback(_window, MWindow::window_mouse_move_callback);
	
		
}



MWindow::~MWindow()
{
	this->isGLFWInitialized = false;
	glfwDestroyWindow(_window);
	glfwTerminate();
}




void MWindow::OnResize(int width, int height)
{
	

	//We cannot set the vulkan context here. Resize can be called outside the thread that is really
	//calling vulkan drawing controls.
	//just flag that the resize ocurred to be processed in the event loop
	_resizeOcurred = true;

}





void MWindow::Redraw()
{
	glfwPostEmptyEvent();
}

void MWindow::AttachEventHandler(IWindowEventHandler* eh)
{
	if (std::find(_handlers.begin(),_handlers.end(),eh) != _handlers.end())
	{
		throw new Exception("Event Handler already exists");
	}
	_handlers.push_back(eh);

}


void MWindow::DetachEventHandler(IWindowEventHandler* eh)
{
    _handlers.remove(eh);
}


