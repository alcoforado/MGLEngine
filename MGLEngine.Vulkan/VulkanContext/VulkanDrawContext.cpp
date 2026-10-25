#include "VulkanDrawContext.h"
#include <MGLEngine.Shared/Resources/ResourceManager.h>
#include <MGLEngine.Shared/Utils/eassert.h>
void VulkanDrawContext::_PushConstant(std::string varName, void* pData, size_t typeIndex, size_t sizeofT) 
{
	eassert(_container.GetResourceManager().GetGlobalBindingsTable()->ValidatePushConstant(_shaderId, varName, typeIndex, sizeofT), "Invalid Push Constant");
	_commandBuffer.PushConstant(pData, sizeofT);
}

