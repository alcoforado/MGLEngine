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
	VkExtent2D _dims;
public:
	VulkanSurface(const VulkanInstance* pInstance,MGL::Window* window);
	~VulkanSurface();
	VkSurfaceKHR GetHandle()const { return _vkSurface; }
	VkExtent2D GetExtent2D() const { return _dims; }

};

