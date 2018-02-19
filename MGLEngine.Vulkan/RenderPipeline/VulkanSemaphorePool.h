#pragma once
#include <MGLEngine.Shared/Utils/PoolBuffer.h>
#include "VulkanSemaphore.h"

class VulkanSemaphorePool : PoolBuffer<VulkanSemaphore>
{
	VulkanLogicalDevice *_pDev;
public:
	VulkanSemaphorePool(VulkanLogicalDevice *dev)
	{
		_pDev = dev;
	}
	~VulkanSemaphorePool()
	{}

	VulkanSemaphore* createNew() override;
};

