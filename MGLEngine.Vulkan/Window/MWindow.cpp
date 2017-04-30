#include "MWindow.h"
#include <glfw/glfw3.h>
bool MGL::Window::isGLFWInitialized = false;

MGL::Window::Window()
{
	_width = 800;
	_height = 640;
	if (!this->isGLFWInitialized)
	{
		int result = glfwInit();
		if (result == 0)
		{
			throw new Exception("Could not initialize GLFW Window");
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
