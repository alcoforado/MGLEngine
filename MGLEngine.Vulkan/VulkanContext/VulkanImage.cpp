#include "VulkanImage.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"

bool VulkanImage::IsHostVisible()
{
	return !_pAllocator->GetDevice().GetPhysicalDevice().GetMemoryProperties()[_allocationInfo.memoryType].HostVisible;
}