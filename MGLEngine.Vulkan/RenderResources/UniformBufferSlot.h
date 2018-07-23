#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include "MGLEngine.Vulkan/Shaders/IVulkanRenderContext.h"
#include <MGLEngine.Shared/Utils/Arrays/ArrayFunctions.h>
#include "IVulkanRenderSlot.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMappedBuffer.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMemoryManager.h>
#include "IVulkanSlotBinding.h"
#include <algorithm>
#include <MGLEngine.Shared/Utils/Observable.h>

/**
 * Represents a Uniform Buffer Slot. A slot just specifies the data that a slot can hold.
 * It also knows how to create a binding for a VulkanDescriptorSet.  The binding is just a junction object between a
 * descriptor set and a slot. It basically contains the  buffer in memory allocated to a VulkanDescriptorSet.
 * Shader Clients generally add data to the slot who flags all its bindings to update.
  *
 */
template<class Data>
class UniformBufferSlot : public IVulkanRenderSlot
{
	const VulkanLogicalDevice *_dev;
	std::vector<Data> _data;
	bool _dirty;
	int _nElems;
	GPUMemoryType _memoryType;
	VkDescriptorSetLayoutBinding _ubo = {};
	Observable<bool> _onChange;
private:

	/**Vulkan Slot Binding inner implementation for UniformBuffer.
	 *
	*/
	class UniformSlotBinding : public IVulkanSlotBinding
	{
	public:
		Listener<bool> _slotListener;
		OPointer<VulkanMappedBuffer<Data>>  pBuffer;
		UniformBufferSlot *pSlot;
		bool bNeedUpdate;

		
		virtual bool NeedUpdate()
		{
			return bNeedUpdate;
		}
		virtual void Update()
		{
			if (NeedUpdate())
			{
				IArray<Data> data = pBuffer->GetMappedArray();
				data.copyFrom(this->pSlot->_data);
				pBuffer->Flush();
				bNeedUpdate = false;
			}
		}

		virtual ~UniformSlotBinding()
		{
		
		}


	};

	
	/*
	 * This function is used internally to bind the vulkan descriptor set with the buffer.
	 * This only happens after the descriptorsetpool is finally allocated, which allocates all descritpor sets,
	 * which in turn, call the bind function for every of its resources.
	 */
	virtual IVulkanSlotBinding* Bind(VulkanDescriptorSet *dsSet)
	{
		UniformSlotBinding *binding = new UniformSlotBinding();
		binding->pBuffer = new VulkanMappedBuffer<Data>(_dev->GetMemoryManager(), _nElems, { VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT });
		binding->pSlot = this;
		binding->bNeedUpdate = true;
		binding->_slotListener.SetHandler([&binding](bool b)
		{
			binding->bNeedUpdate = true;
		});

		VkDescriptorBufferInfo bufferInfo;
		bufferInfo.buffer = binding->pBuffer->GetHandle();
		bufferInfo.offset = 0;
		VkWriteDescriptorSet descWrite;
		descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descWrite.dstSet = dsSet->GetDescriptorSetHandle();
		descWrite.dstBinding = _ubo.binding;
		descWrite.dstArrayElement = 0;
		descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descWrite.descriptorCount = 1;
		descWrite.pBufferInfo = &bufferInfo;
		descWrite.pImageInfo = nullptr;
		descWrite.pTexelBufferView = nullptr;
		vkUpdateDescriptorSets(_dev->GetHandle(), 1, &descWrite, 0, nullptr);

		return binding;
	}


public:
	UniformBufferSlot(VulkanMemoryManager *mngr, int binding, int nElems, std::vector<VkShaderStageFlagBits> stages, GPUMemoryType memType, ResourceWriteFrequency frequency)
		:IVulkanRenderSlot(frequency)
	{
		assert(nElems > 0);

		_dev = mngr->GetLogicalDevice();
		_ubo.binding = binding;
		_ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		_ubo.descriptorCount = 1;
		_ubo.pImmutableSamplers = nullptr;
		_ubo.stageFlags = ArrayFunctions::FromBitFlagsToInt(stages);
		
		_nElems = nElems;
		_memoryType = memType;
		_data.resize(nElems);

	}



	virtual ~UniformBufferSlot()
	{


	}
	virtual bool Compatible(IRenderResource *res)
	{
		return res == this;
	}
	virtual void SetData(Data data)
	{
		this->_data[0] = data;
		this->_dirty = true;
	}

	virtual bool IsDirty() override {
		return _dirty;
	}

	virtual VkDescriptorSetLayoutBinding GetVkDescriptorSetLayoutBinding()
	{
		return _ubo;
	}



	virtual GPUMemoryType MemoryType() override
	{
		return _memoryType;
	}

};

