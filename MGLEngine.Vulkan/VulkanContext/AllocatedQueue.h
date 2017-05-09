#pragma once

#include <vulkan/vulkan.h>
class VulkanLogicalDevice;
class AllocatedQueue
{
private:
	const VulkanLogicalDevice& _logicalDevice;
	VkQueue _handle;
	int _queueIndex;
	int _familyIndex;
public:


	AllocatedQueue(const VulkanLogicalDevice &logicalDevice, int familyIndex, int queueIndex);
	~AllocatedQueue();

	//Getters
	int GetFamilyIndex() const { return _familyIndex; }
	VkQueue GetHandle() const { return _handle; }
	int GetQueueIndex() const { return _queueIndex; }
};

