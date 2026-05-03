#pragma once
#include <vulkan/vulkan.h>
#include <vector>


class FrameData {
public:
	VkImage image;
	VkImageView imageView;
	VkFramebuffer framebuffer;
};
class SwapChainData {

	public:
		VkSwapchainKHR handle=VK_NULL_HANDLE;
		VkFormat imageFormat;
		VkColorSpaceKHR imageColorSpace;
		std::vector<FrameData> frames;
		VkExtent2D dims = {};
		int activeFrame = 0;
		uint32_t currentImageIndex=0;
		SwapChainData() {
			dims = {0,0};
			imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		
		}

		FrameData& GetActiveFrame() {
			return frames[activeFrame];
		}
		void NextFrame() {
			activeFrame = (activeFrame + 1);
			if (activeFrame == frames.size())
				activeFrame = 0;
		}
};
