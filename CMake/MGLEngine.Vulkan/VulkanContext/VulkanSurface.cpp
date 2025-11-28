#include "VulkanSurface.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "../VulkanUtils.h"
#include <cassert>
#include <algorithm>


VulkanSurface::VulkanSurface(const  VulkanInstance* pInstance, MGL::Window* window)
{
	_vkInstance = pInstance->GetHandle();
	VkResult err = glfwCreateWindowSurface(_vkInstance, window->GLFWHandler(), NULL, &_vkSurface);
	_dims.height = static_cast<unsigned>(window->Height());
	_dims.width =  static_cast<unsigned>(window->Width());
	AssertVulkanSuccess(err);
}




VulkanSurface::~VulkanSurface()
{
	vkDestroySurfaceKHR(_vkInstance, _vkSurface, nullptr);
}

