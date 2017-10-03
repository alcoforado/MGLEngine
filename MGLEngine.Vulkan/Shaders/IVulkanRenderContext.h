#pragma once
#include "../VulkanContext/VulkanSwapChain.h"
#include "../RenderPipeline/VulkanCommandPool.h"
#include "../MemoryManager/VulkanMemoryManager.h"

class  IVulkanRenderContext
{
public:
	IVulkanRenderContext();
	virtual ~IVulkanRenderContext();
	virtual const VulkanSwapChain& GetSwapChain() const = 0;
	virtual const VulkanLogicalDevice* GetLogicalDevice() const = 0;
	virtual const VulkanCommandPool* GetCommandPool() const =0;
	virtual VulkanMemoryManager* GetMemoryManager()  =0;
};

