#include "ResourceManager.h"
#include <stb_image.h>
#include <gli/gli.hpp>
#include <filesystem>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanLogicalDevice.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>
ImgHandler ResourceManager::LoadImage(ImageConfig config)
{
	ImageResource res;

	res.Name = config.filePath;
	
	/*
	std::string ext = std::filesystem::path(config.filePath).extension().string();
	if (ext == ".jpg" || ext == ".jpeg" || ext==".bmp" || ext ==".png")
	*/

	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(config.filePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	eassert(pixels,std::format("failed to load texture image for {}",config.filePath))
	VkDeviceSize imageSize = texWidth * texHeight * VulkanImage::GetTexelSize(VK_FORMAT_R8G8B8A8_SRGB);

	VulkanBuffer stagingBuffer=this->_memory.CreateStagingBuffer(imageSize);
	stagingBuffer.ToGPU(pixels, imageSize);
	stbi_image_free(pixels);


	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = static_cast<uint32_t>(texWidth);
	imageInfo.extent.height = static_cast<uint32_t>(texHeight);
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.flags = 0; // Optional

	res.Image = this->_memory.CreateImageBuffer(imageInfo);

	auto pCommandBuffer = _device.GetGraphicQueue().CreateCommandBuffer();
	pCommandBuffer->BeginOnce();
	pCommandBuffer->TransitionImageToCopyTarget(res.Image);
	pCommandBuffer->CopyToImage(stagingBuffer, res.Image);
	pCommandBuffer->TransitionImageToFinalLayout(res.Image);
	pCommandBuffer->End();
	_device.GetGraphicQueue().Submit(*pCommandBuffer);
	_device.WaitToBeIdle();
	pCommandBuffer->Delete();


	auto id = this->_images.size();
	this->_images.push_back(res);
	return ImgHandler(id);

}