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
		VkExtent2D dims;
		uint32_t currentImageIndex=0;
		SwapChainData() {}
};
