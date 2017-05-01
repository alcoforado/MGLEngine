#include "MWindow.h"
#include <Utils/Exception.h>
bool MGL::Window::isGLFWInitialized = false;

MGL::Window::Window()
{
	_width = 800;
	_height = 640;
	_window = NULL;
	if (!this->isGLFWInitialized)
	{
		int result = glfwInit();
		if (result == 0)
		{
			throw new Exception("Could not initialize GLFW Window");
		}
		isGLFWInitialized = true;
		
		_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!_window)
		{
			throw new Exception("Create Window failed");
		}

	}
}


MGL::Window::~Window()
{
}

void MGL::Window::SetSize(int width, int height)
{
	_width = width;
	_height = height;
}

void MGL::Window::EasyRun()
{

	
}
