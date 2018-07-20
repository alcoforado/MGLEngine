#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include "MGLEngine.Vulkan/Shaders/IVulkanRenderContext.h"
#include <MGLEngine.Shared/Utils/Arrays/ArrayFunctions.h>
#include "IVulkanRenderSlot.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMappedBuffer.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMemoryManager.h>
template<class Data>
class UniformBufferBinding : public IVulkanRenderSlot
{
	const VulkanLogicalDevice *_dev;
	std::vector<Data> _data;
	bool _dirty;
	VulkanMappedBuffer<Data>  *_buffer;
	VkDeviceMemory _bufferMemory;
	GPUMemoryType _memoryType;
	VkDescriptorSetLayoutBinding _ubo = {};
	VulkanDescriptorSet* _dsSet = nullptr;
	
	
private:
	/*
	 * This function is used internally to bind the vulkan descriptor set with the buffer.
	 * This only happens after the descriptorsetpool is finally allocated, which allocates all descritpor sets,
	 * which in turn, call the bind function for every of its resources.
	 */
	virtual void Bind(VulkanDescriptorSet *dsSet)
	{
		_dsSet = dsSet;
		
		VkDescriptorBufferInfo bufferInfo;
		bufferInfo.buffer = _buffer->GetHandle();
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
	}


public:
	UniformBufferBinding(VulkanMemoryManager *mngr,int binding, int nElems, std::vector<VkShaderStageFlagBits> stages,GPUMemoryType memType, ResourceWriteFrequency frequency)
		:IVulkanRenderSlot(frequency)
	{
		assert(nElems > 0);

		_dev = mngr->GetLogicalDevice();
		_ubo.binding = binding;
		_ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		_ubo.descriptorCount = 1;
		_ubo.pImmutableSamplers = nullptr;
		_ubo.stageFlags = ArrayFunctions::FromBitFlagsToInt(stages);

		_memoryType = memType;
		_data.resize(nElems);

		_buffer = new VulkanMappedBuffer<Data>(mngr, nElems, { VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT });
		//createBuffer(sizeof(Data), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory)
	}

	virtual void Load(IVulkanResourceLoadContext *context) override {
		if (IsDirty())
		{
			IArray<Data> data = _buffer->GetMappedArray();
			data.copyFrom(this->_data);
			_buffer->Flush();
			_dirty = false;
		}
	}
	virtual VkDescriptorSetLayoutBinding GetVulkanDescriptor() const override
	{
		return _ubo;
	}


	virtual ~UniformBufferBinding()
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
	

	virtual GPUMemoryType MemoryType() override
	{
		return _memoryType;
	}

};

