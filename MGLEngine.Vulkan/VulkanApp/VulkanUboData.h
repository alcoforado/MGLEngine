#pragma once
#include <vector>
#include <deque>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/Pool.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <stddef.h>

struct VulkanUboBufferElem {
	s_ptr<VulkanBuffer> pBuffer;
	bool dirty;
};
typedef Pool<std::vector<std::byte>>::Handle VecOfBytesHandle;

struct VulkanUboState {
	VecOfBytesHandle valueToCopy;
	size_t bufferStartIndex;
	bool inQueue;
	size_t dirtyFrames; // number of dirty frames
};

class VulkanUboData
{
	unsigned framesInFlight;
	static const int NULL_INDEX = -1;

public:

	std::vector<VulkanUboBufferElem> buffers;
	std::vector<VulkanUboState> uboStates;
	std::deque<int> activeUboState;

	VulkanUboData(unsigned framesInFlight)
		:framesInFlight(framesInFlight)
	{

	}

	size_t AddUbo(const std::vector<s_ptr<VulkanBuffer>>& uboBuffers)
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
	void AddAssignment(int uboIndex, VecOfBytesHandle data)
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
		for (unsigned i = 0; i < framesInFlight; i++)
		{
			buffers[k++].dirty = true;
		}
		uboState.dirtyFrames = this->framesInFlight;
		uboState.valueToCopy = data;
	}

	bool CheckAllBuffersClean(unsigned index) {
		auto& uboState = uboStates[index];
		size_t k = uboState.bufferStartIndex;
		for (unsigned i = 0; i < framesInFlight; i++)
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
		//First clean the kitchen, befor adding dishes.
		while (!activeUboState.empty() && activeUboState.front() == NULL_INDEX)
		{
			activeUboState.pop_front();
		}
		int index = 0;
		for (auto uboIndex : activeUboState)
		{
			VulkanUboState& uboState = uboStates[uboIndex];
			VulkanUboBufferElem& buffer = buffers[uboState.bufferStartIndex + frameIndex];
			if (buffer.dirty) //nothing to be done if not dirty
			{
				buffer.pBuffer->CopyToGPU(uboState.valueToCopy->Data().data(), uboState.valueToCopy->Data().size());
				buffer.dirty = false;
				uboState.dirtyFrames--;
				if (uboState.dirtyFrames == 0)
				{

					activeUboState[index] = NULL_INDEX;
					uboState.inQueue = false;
					eassert(CheckAllBuffersClean(uboIndex), "Inconsisteny found, all buffers should be clear, but at least one is dirty");
				}
			}
			index++;

		}

	}

	

	s_ptr<VulkanBuffer> GetBuffer(unsigned frameIndex, size_t uboIndex)
	{
		eassert(uboIndex < uboStates.size(), "Index out of range");
		return buffers[uboStates[uboIndex].bufferStartIndex + frameIndex].pBuffer;
	}

	void Dispose() {
		for (auto& elem : buffers)
		{
			elem.pBuffer->Delete();
		}
		buffers.clear();
		uboStates.clear();
		activeUboState.clear();
		return;
	}


};