
#pragma once
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanImage.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/utils.h>
#include <vector>
#include <vulkan/vulkan.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBuffer.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include <MGLEngine.Shared/ResourceLoaders/ImageLoader.h>
struct ImageResource {
	std::string Name;
	VulkanImage Image;

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

/**
Resource Manager should have one instance per physical device.
It contains all resources loaded by shader. Uniform Buffers and Images.
It is responsible to load and store them in memory.
*/
class ResourceManager {


	VulkanMemoryAllocator& _memory;
	const VulkanLogicalDevice& _device;
	std::vector<ImageResource> _images;
	ImageLoader _imageLoader;
	//u_ptr<VulkanCommandBuffer> _pCommandBuffer;
public:
	ResourceManager(VulkanMemoryAllocator& memory,const VulkanLogicalDevice &device)
		:_memory(memory),_device(device) {
		////_pCommandBuffer = _device.GetGraphicQueue().CreateCommandBuffer();
	}
	ImgHandler LoadImage(ImageConfig confi);
};

