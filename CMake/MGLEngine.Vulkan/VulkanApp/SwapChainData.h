#include <vulkan/vulkan.h>
#include <vector>
class SwapChainData {

	public:
		VkSwapchainKHR handle=VK_NULL_HANDLE;
		VkFormat imageFormat;
		VkColorSpaceKHR imageColorSpace;
		VkExtent2D dims;
		std::vector<VkImage> images;
		std::vector<VkImageView> imagesviews;
		uint32_t currentImageIndex=0;
};
