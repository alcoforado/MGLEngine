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

void window_size_callback(GLFWwindow* window, int width, int height)
{
	auto This = static_cast<MGL::Window*>(glfwGetWindowUserPointer(window));
	
	This->OnResize(width, height);

}



MGL::Window::Window()
{
	_width = 800;
	_height = 640;
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
		_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		glfwSetWindowUserPointer(_window, this);
		if (!_window)
		{
			throw new Exception("Create Window failed");
		}

		

		//Initialize Vulkan
		_vkContext = new VulkanContext(_window);

		//Register resize event
		glfwSetWindowSizeCallback(_window, window_size_callback);
}



MGL::Window::~Window()
{
	this->isGLFWInitialized = false;
	glfwTerminate();
}




void MGL::Window::OnResize(int width, int height)
{
	_width = width;
	_height = height;

	//We cannot set the vulkan context here. Resize can be called outside the thread that is really
	//calling vulkan drawing controls.
	//just flag that the resize ocurred to be processed in the event loop
	_resizeOcurred = true;

}


void MGL::Window::SetSize(int width, int height)
{
	_width = width;
	_height = height;
	glfwSetWindowSize(_window, _width, _height);
}

void MGL::Window::EasyRun()
{
	assert(_window);
	_isEasyRun = true;

	while (!glfwWindowShouldClose(_window))
	{
		glfwWaitEvents();
		if (_resizeOcurred)
		{
			_vkContext->GetLogicalDevice()->WaitToBeIdle();
			_vkContext->OnResize(_window, _width, _height);
			_vkContext->Draw();
			_resizeOcurred = false;
		}
		else
		{

			_vkContext->Draw();
		}
		

	}
	
}


void MGL::Window::PsychoRun()
{
	assert(_window);
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		if (_resizeOcurred)
		{
			_vkContext->GetLogicalDevice()->WaitToBeIdle();
			_vkContext->OnResize(_window, _width, _height);
			_vkContext->Draw();
			_resizeOcurred = false;
		}
		else
		{
			_vkContext->Draw();
		}
	}
	
}

void MGL::Window::Redraw()
{
	glfwPostEmptyEvent();
}

