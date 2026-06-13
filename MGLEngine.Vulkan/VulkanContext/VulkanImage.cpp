#include "VulkanImage.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include <vulkan/utility/vk_format_utils.h>
#include <MGLEngine.Shared/utils.h>

void VulkanImage::AssertIsNotDeleted() const
{
	eassert(_handle != VK_NULL_HANDLE, "Image was deleted");
}

VulkanImage::VulkanImage(VulkanMemoryAllocator* pAllocator, VkImage img, VkImageCreateInfo createInfo, const VmaAllocation& allocation, const VmaAllocationInfo& allocationInfo)

	{
		_pAllocator = pAllocator;
		_handle = img;
		_allocation = allocation;
		_allocationInfo = allocationInfo;
		_createInfo = createInfo;
		_currentLayout = _createInfo.initialLayout;
		_format = createInfo.format;
		_accessFlags = VK_ACCESS_NONE; //Image is created but not yet defined. No Read, Writes allowed
		eassert(createInfo.extent.depth > 0 && createInfo.extent.width > 0 && createInfo.extent.height > 0, "Invalid Extent Parameters");
		_sizeInBytes = _createInfo.extent.width*_createInfo.extent.height*_createInfo.extent.depth*VulkanImage::GetTexelSize(_format);

	}


VkDeviceSize VulkanImage::GetTexelSize(VkFormat format)
{
	switch (format)
	{
		case VK_FORMAT_R8G8B8A8_SRGB:
			return 4;
		default:
		{
			throw_error("Unknown VkFormat");
			break;
		}
	};

}


void VulkanImage::Delete()
{

	AssertIsNotDeleted();
	vmaDestroyImage(_pAllocator->GetVmaAllocator(), _handle, _allocation);
	_handle = VK_NULL_HANDLE;
	_pAllocator = nullptr;

}

bool VulkanImage::IsHostVisible()
{
	AssertIsNotDeleted();
	return !_pAllocator->GetDevice().GetPhysicalDevice().GetMemoryProperties()[_allocationInfo.memoryType].HostVisible;
}