#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <MGLEngine.Vulkan/VulkanContext/VulkanSemaphore.h>
class VulkanFence;
class VulkanCommandBuffer;
class VulkanCommandPool;
class VulkanLogicalDevice;
class VulkanQueue
{
private:
	const VulkanLogicalDevice& _logicalDevice;
	VkQueue _handle;
	std::shared_ptr<VulkanCommandPool> _pCommandPool;
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
	const VulkanLogicalDevice& GetLogicalDevice() const { return _logicalDevice; }
	//Submit command
	void Submit(VulkanCommandBuffer &cb) const;
	void Submit(const std::vector<VulkanCommandBuffer*>& vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages,VulkanFence *fence=nullptr) const;
	void Submit(VulkanCommandBuffer* cb, VulkanSemaphore* pSignal, VulkanSemaphore* pWait, VkPipelineStageFlags waitStages, VulkanFence* fence) const;
	VkResult Present(VkSwapchainKHR swapChain, uint32_t imageIndex, VulkanSemaphore* toWait) const;

	//Create Command Buffers
	std::shared_ptr<VulkanCommandBuffer> CreateCommandBuffer();


	void WaitIdle() const;
};

