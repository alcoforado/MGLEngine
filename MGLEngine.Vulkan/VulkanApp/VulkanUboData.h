#pragma once
#include <vector>
#include <deque>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <stddef.h>

struct VulkanUboBufferElem {
	s_ptr<VulkanBuffer> pBuffer;
	bool dirty;
};

struct VulkanUboState {
	std::vector<std::byte> valueToCopy;
	size_t bufferStartIndex;
	bool inQueue;
	size_t dirtyFrames; // number of dirty frames
};

class VulkanUboData
{
	unsigned framesInFlight;
	static const size_t NULL_INDEX = -1;

public:

	std::vector<VulkanUboBufferElem> buffers;
	std::vector<VulkanUboState> uboStates;
	std::deque<int> activeUboState;

	VulkanUboData(unsigned framesInFlight)
		:framesInFlight(framesInFlight)
	{

	}

	unsigned AddUbo(const std::vector<s_ptr<VulkanBuffer>>& uboBuffers)
	{
		eassert(uboBuffers.size() == framesInFlight, "Expect buffers size equal to frames in flight ");
		auto resultIndex = uboStates.size();
		uboStates.push_back(VulkanUboState{
			.bufferStartIndex = buffers.size(),
			.inQueue = false,
			.dirtyFrames = 0
			});

		for (auto b : uboBuffers)
		{
			buffers.push_back(VulkanUboBufferElem{
				.pBuffer = b,
				.dirty = false

				});
		}
		return resultIndex;
	}
	//data will be garbage after it
	void AddAssignment(size_t uboIndex, std::vector<std::byte>& data)
	{
		auto& uboState = uboStates[uboIndex];
		//add to queue if not found
		if (!uboState.inQueue)
		{
			activeUboState.push_back(uboIndex);
			uboState.inQueue = true;
		}


		//first of all, dirt all buffers
		size_t k = uboState.bufferStartIndex;
		for (int i = 0; i < framesInFlight; i++)
		{
			buffers[k++].dirty = true;
		}
		uboState.dirtyFrames = this->framesInFlight;
		uboState.valueToCopy.swap(data);
	}

	bool CheckAllBuffersClean(unsigned index) {
		auto& uboState = uboStates[index];
		size_t k = uboState.bufferStartIndex;
		for (int i = 0; i < framesInFlight; i++)
		{
			if (buffers[k++].dirty)
			{
				return false;
			}
		}
		return true;
	}
	

	void ProcessAssignment(unsigned frameIndex)
	{
		eassert(frameIndex < framesInFlight, "Invalid frame index");
		//First clean the kitchen, befor add dishes.
		while (activeUboState.front() == NULL_INDEX)
		{
			activeUboState.pop_front();
		}
		int index = 0;
		for (auto uboIndex : activeUboState)
		{
			VulkanUboState& uboState = uboStates[uboIndex];
			VulkanUboBufferElem& buffer = buffers[uboState.bufferStartIndex + frameIndex];
			eassert(buffer.dirty, "Panic serious misallignment");
			buffer.pBuffer->CopyToGPU(uboState.valueToCopy.data(), uboState.valueToCopy.size());
			buffer.dirty = false;
			uboState.dirtyFrames--;
			if (uboState.dirtyFrames == 0)
			{

				activeUboState[index] = NULL_INDEX;
				uboState.inQueue = false;
				eassert(CheckAllBuffersClean(uboIndex), "Inconsisteny found, all buffers should be clear, but at least one is dirty");
			}
			index++;

		}

	}



};