
#include "VulkanCommandBatchCollection.h"
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>

void VulkanCommandBatchCollection::AddBatch(const std::vector<VulkanCommandBuffer*>& vcb, VulkanSemaphore *pSignal, VulkanSemaphore *pWait, const std::vector<VkPipelineStageFlagBits>& waitStages)
{

	BatchInfo *bi = new BatchInfo();


	bi->_cbs.resize(vcb.size());
	for (int i = 0; i<vcb.size(); i++)
	{
		bi->_cbs[i] = vcb[i]->GetHandle();
	}

	if (pSignal != nullptr)
	{
		bi->_signals.push_back(pSignal->GetHandle());
	}
	if (pWait != nullptr)
	{
		bi->_waits.push_back(pWait->GetHandle());
	}
	bi->_waitStages.push_back(FromBitFlagsToInt(waitStages));

	VkSubmitInfo submitInfo = {};

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = (uint32_t) bi->_cbs.size();
	submitInfo.pCommandBuffers = bi->_cbs.data();
	submitInfo.pSignalSemaphores = bi->_signals.size() != 0 ? bi->_signals.data() : nullptr;
	submitInfo.signalSemaphoreCount = (uint32_t) bi->_signals.size();
	submitInfo.pWaitSemaphores = bi->_waits.size() != 0 ? bi->_waits.data() : nullptr;;
	submitInfo.waitSemaphoreCount = (uint32_t)bi->_waits.size();
	submitInfo.pWaitDstStageMask = bi->_waitStages.data();

	_batchInfos.push_back(bi);
	_submitInfos.push_back(submitInfo);
}


