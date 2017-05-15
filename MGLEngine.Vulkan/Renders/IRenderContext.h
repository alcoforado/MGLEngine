#pragma once
#include "../VulkanContext/VulkanSwapChain.h"

class  IRenderContext
{
public:
	IRenderContext();
	virtual ~IRenderContext();
	virtual const VulkanSwapChain& GetSwapChain() const = 0;
};

