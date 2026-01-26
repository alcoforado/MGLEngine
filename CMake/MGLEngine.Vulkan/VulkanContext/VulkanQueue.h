#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "MGLEngine.Vulkan/RenderPipeline/VulkanSemaphore.h"
#include <memory>
#include "VulkanCommandBatchCollection.h"
class VulkanFence;
class VulkanCommandBuffer;
class VulkanLogicalDevice;
class VulkanQueue
{
private:
	const VulkanLogicalDevice& _logicalDevice;
	VkQueue _handle;
	bool _isPresentationQueue;
	bool _isGraphicQueue;
	int _queueIndex;
	int _familyIndex;
public:


	VulkanQueue(const VulkanLogicalDevice &logicalDevice, int familyIndex, int queueIndex);
	~VulkanQueue();

	//Getters
	int GetFamilyIndex() const { return _familyIndex; }
	VkQueue GetHandle() const { return _handle; }
	int GetQueueIndex() const { return _queueIndex; }

	//Submit command
	void Submit(VulkanCommandBuffer &cb) const;
	void Submit(const std::vector<VulkanCommandBuffer*>& vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages,VulkanFence *fence=nullptr) const;
	void Submit(VulkanCommandBuffer* cb, VulkanSemaphore* pSignal, VulkanSemaphore* pWait, VkPipelineStageFlags waitStages, VulkanFence* fence) const;
	void Present(VkSwapchainKHR swapChain, uint32_t imageIndex, VulkanSemaphore* toSignal) const;

	void Submit(VulkanCommandBatchCollection &cl,VulkanFence *fence=nullptr) const;
	void WaitIdle() const;
};

