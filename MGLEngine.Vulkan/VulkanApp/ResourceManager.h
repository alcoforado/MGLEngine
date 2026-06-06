
#pragma once
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <vector>


struct ImageResource {
	std::string name;

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
	std::vector<ImageResource> _images;
public:
	ResourceManager(VulkanMemoryAllocator& memory)
		:_memory(memory) {}
	ImgHandler LoadImage(ImageConfig confi);
};

