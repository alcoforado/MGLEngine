#pragma once
#include <MGLEngine.Vulkan/DrawTree/TreeExecutionContext.h>
class IVulkanResourceLoader {
public:
	void virtual OnFrameInit(TreeExecutionContext* pContext)=0;
	void virtual OnExecution(TreeExecutionContext* pContext)=0;
};
