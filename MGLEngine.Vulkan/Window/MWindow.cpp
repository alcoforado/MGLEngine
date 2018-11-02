#include "MWindow.h"
#include <Utils/Exception.h>
#include <cassert>
#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>
#include "../VulkanContext/VulkanContext.h"
#include <MGLEngine.Shared/Window/IWindowEventHandler.h>
#include <MGLEngine.Shared/Window/ICanvas.h>
#include <MGLEngine.Vulkan/Window/VulkanCanvas.h>
#include <MGLEngine.Shared/ShapesService/ShapesService.h>
bool MGL::Window::isGLFWInitialized = false;

#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

void window_size_callback(GLFWwindow* window, int width, int height)
{
	auto This = static_cast<MGL::Window*>(glfwGetWindowUserPointer(window));
	
	This->OnResize(width, height);

}


void MGL::Window::window_mouse_move_callback(GLFWwindow* window, double x, double y)
{
	MGL::Window *w = static_cast<MGL::Window*>(glfwGetWindowUserPointer(window));
	for(auto it: w->_handlers)
	{
		it->OnMouseMove(x, y);
	}
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

		//Register mouse move event
		glfwSetCursorPosCallback(_window, MGL::Window::window_mouse_move_callback);
		_canvas = new VulkanCanvas(this);

		//Create ShapeService
		_shService = new ShapesService(this);

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

void MGL::Window::AttachEventHandler(IWindowEventHandler* eh)
{
	if (std::find(_handlers.begin(),_handlers.end(),eh) != _handlers.end())
	{
		throw new Exception("Event Handler already exists");
	}
	_handlers.push_back(eh);

}


void MGL::Window::DetachEventHandler(IWindowEventHandler* eh)
{
    _handlers.remove(eh);
}

ICanvas* MGL::Window::GetCanvas()
{
	return _canvas;
}

ShapesService * MGL::Window::GetShapesManager()
{
	return _shService;
}

