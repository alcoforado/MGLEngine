#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
class GLFWWindow;

struct InstanceLayer {
	VkLayerProperties layer;
	std::vector<VkExtensionProperties> extensions;
};

class VulkanContext
{

private:
	
	VkInstance _vkInstance;
public:
	VulkanContext();
	~VulkanContext();
	void Initialize(GLFWWindow* window);
	std::vector<InstanceLayer> GetLayerProperties();
	std::string MapVkResultToString(VkResult result);
};

