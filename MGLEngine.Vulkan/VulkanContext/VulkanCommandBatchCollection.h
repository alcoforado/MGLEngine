#pragma once

#include <vulkan/vulkan.h>
#include <vector>
class VulkanCommandBuffer;
class VulkanAllocatedQueue;
class VulkanSemaphore;
class BatchInfo
{
public:
	std::vector<VkCommandBuffer> _cbs;
	std::vector<VkSemaphore> _waits;
	std::vector<VkSemaphore> _signals;
	std::vector<VkFlags> _waitStages;
};


class VulkanCommandBatchCollection
{
	friend class VulkanAllocatedQueue;

	
	public:
	
	
private:
	std::vector<VkSubmitInfo> _submitInfos;
	std::vector<BatchInfo*> _batchInfos;
public:


	void AddBatch(const std::vector<VulkanCommandBuffer*>& vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages);
	
	

	


};
