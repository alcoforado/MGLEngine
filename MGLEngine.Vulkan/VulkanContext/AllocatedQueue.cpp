#include "AllocatedQueue.h"

AllocatedQueue::AllocatedQueue(VulkanLogicalDevice logicalDevice, int familyIndex, int queueIndex)
	:_logicalDevice(logicalDevice),_familyIndex(familyIndex),_queueIndex(queueIndex)
{
	vkGetDeviceQueue(_logicalDevice.GetHandle(), _familyIndex, _queueIndex,&_handle);
}




AllocatedQueue::~AllocatedQueue()
{
}
