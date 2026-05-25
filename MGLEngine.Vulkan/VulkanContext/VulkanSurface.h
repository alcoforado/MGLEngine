#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <glfw/glfw3.h>
#include <MGLEngine.Vulkan/Window/MWindow.h>
class VulkanInstance;


class VulkanSurface
{
	VkSurfaceKHR _vkSurface;
	VkInstance _vkInstance;
	MGL::Window* _pWindow;
public:
	VulkanSurface(const VulkanInstance* pInstance,MGL::Window* window);
	~VulkanSurface();
	VkSurfaceKHR GetHandle()const { return _vkSurface; }
	VkExtent2D GetExtent2D() const { 
		auto sz = _pWindow->Size();
		return {
			.width  = static_cast<uint32_t>(sz.width),
			.height = static_cast<uint32_t>(sz.height)
		};
		 
	
	}

};

