#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <glfw/glfw3.h>
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Window/MWindow.h>
class VulkanInstance;

class VulkanSurface
{
	VkSurfaceKHR _vkSurface;
	VkInstance _vkInstance;
	s_ptr<MWindow> _pWindow;
public:
	VulkanSurface(const VulkanInstance* pInstance,s_ptr<MWindow> window);
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

