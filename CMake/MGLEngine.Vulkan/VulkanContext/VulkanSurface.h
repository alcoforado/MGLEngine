#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <glfw/glfw3.h>
#include <MGLEngine.Vulkan/Window/MWindow.h>
class VulkanInstance;
struct PresentationGraphicsFamilyIndices
{
	uint32_t GraphicQueueFamily;
	uint32_t PresentationQueueFamily;
};

class VulkanSurface
{
	VkSurfaceKHR _vkSurface;
	VkInstance _vkInstance;
public:
	VulkanSurface(const VulkanInstance* pInstance,MGL::Window* window);
	~VulkanSurface();
	VkSurfaceKHR GetHandle()const { return _vkSurface; }
};

