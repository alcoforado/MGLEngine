
#pragma once
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <vector>
class ResourceManager {


	VulkanMemoryAllocator& _memory;
	std::vector<ImageResource> _images;
public:
	ResourceManager(VulkanMemoryAllocator& memory)
		:_memory(memory) {}
	ImgHandler LoadImage(ImageConfig confi);
};

class ImageResource {
	std::string resourceName;
	
};

class ImgHandler {
	int id;

public:
	int GetId() const { return id; }
};