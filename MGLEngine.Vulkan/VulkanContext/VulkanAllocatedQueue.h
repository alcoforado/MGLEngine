#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "MGLEngine.Vulkan/RenderPipeline/VulkanSemaphore.h"
#include <memory>
#include "VulkanCommandBatchCollection.h"
class VulkanCommandBuffer;
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

	//Submit command
	void Submit(VulkanCommandBuffer &cb) const;
	void Submit(const std::vector<VulkanCommandBuffer*>& vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages) const;

	void Submit(VulkanCommandBatchCollection &cl);
	void WaitIdle() const;
};

