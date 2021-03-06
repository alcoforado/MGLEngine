#pragma once

#include <vulkan/vulkan.h>
#include <vector>
class VulkanCommandBuffer;
class VulkanQueue;
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
	friend class VulkanQueue;

	
	public:
	
	
private:
	std::vector<VkSubmitInfo> _submitInfos;
	std::vector<BatchInfo*> _batchInfos;
public:


	void AddBatch(const std::vector<VulkanCommandBuffer*>& vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages);
	void AddBatch(VulkanCommandBuffer* vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages);
	void Clear()
	{
		_submitInfos.clear();
		for (auto e: _batchInfos){delete e;}
		_batchInfos.clear();
	}
	
	void AddBatch(VulkanCommandBatchCollection *batch);

	


};
