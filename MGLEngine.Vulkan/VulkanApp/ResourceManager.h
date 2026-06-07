
#pragma once
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <vector>
#include <vulkan/vulkan.h>

struct ImageResource {
	std::string Name;
	VkImage Handle;

};

class ImgHandler {
	std::size_t id;

public:
	ImgHandler(std::size_t id)
	{
		this->id = id;
	}
	std::size_t GetId() const { return id; }
};

class ResourceManager {


	VulkanMemoryAllocator& _memory;
	VulkanLogicalDevice& _device;
	std::vector<ImageResource> _images;
public:
	ResourceManager(VulkanMemoryAllocator& memory,VulkanLogicalDevice &device)
		:_memory(memory),_device(device) {}
	ImgHandler LoadImage(ImageConfig confi);
};

