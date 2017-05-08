#pragma once

#include <vulkan/vulkan.h>
#include "VulkanLogicalDevice.h"

class AllocatedQueue
{
	VulkanLogicalDevice _logicalDevice;
	VkQueue _handle;
	int _queueIndex;
	int _familyIndex;
public:


	AllocatedQueue(VulkanLogicalDevice logicalDevice, int familyIndex, int queueIndex);
	~AllocatedQueue();

	//Getters
	int GetFamilyIndex() const { return _familyIndex; }
	VkQueue GetHandle() const { return _handle; }
	int GetQueueIndex() const { return _queueIndex; }
};

