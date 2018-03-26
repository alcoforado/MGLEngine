#pragma once
#include "../VulkanContext/VulkanSwapChain.h"
#include "../RenderPipeline/VulkanCommandPool.h"
#include "../MemoryManager/VulkanMemoryManager.h"

class  IVulkanRenderContext
{
public:
	IVulkanRenderContext();
	virtual ~IVulkanRenderContext();
	virtual VulkanSwapChain* GetSwapChain() const = 0;
	virtual VulkanLogicalDevice* GetLogicalDevice() const = 0;
	virtual VulkanMemoryManager* GetMemoryManager()  =0;
};

