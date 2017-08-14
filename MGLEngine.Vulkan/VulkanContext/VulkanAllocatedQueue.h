#pragma once

#include <vulkan/vulkan.h>

class VulkanLogicalDevice;
class VulkanAllocatedQueue
{
private:
	const VulkanLogicalDevice& _logicalDevice;
	VkQueue _handle;
	int _queueIndex;
	int _familyIndex;
public:


	VulkanAllocatedQueue(const VulkanLogicalDevice &logicalDevice, int familyIndex, int queueIndex);
	~VulkanAllocatedQueue();

	//Getters
	int GetFamilyIndex() const { return _familyIndex; }
	VkQueue GetHandle() const { return _handle; }
	int GetQueueIndex() const { return _queueIndex; }
};

