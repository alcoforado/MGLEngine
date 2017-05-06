#include "MWindow.h"
#include <Utils/Exception.h>
#include <cassert>

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>
#include "../VulkanContext/VulkanContext.h"
bool MGL::Window::isGLFWInitialized = false;

#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

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
		
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!_window)
		{
			throw new Exception("Create Window failed");
		}

		

		//Initialize Vulkan
		_vkContext = new VulkanContext();

		_vkContext->Initialize(_window);
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
	assert(_window);
	while (!glfwWindowShouldClose(_window))
	{
		glfwWaitEvents();
	}
	
}


void MGL::Window::PsychoRun()
{
	assert(_window);
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
	}
	
}

