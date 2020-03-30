#include "VulkanSemaphorePool.h"





VulkanSemaphore* VulkanSemaphorePool::createNew()
{
	return new VulkanSemaphore(_pDev);

}
