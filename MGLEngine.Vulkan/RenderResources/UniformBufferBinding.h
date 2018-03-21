#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include "MGLEngine.Vulkan/Shaders/IVulkanRenderContext.h"
#include <MGLEngine.Shared/Utils/Arrays/ArrayFunctions.h>
#include "IVulkanRenderResource.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanMappedBuffer.h>
template<class Data>
class UniformBufferBinding : public IVulkanRenderResource
{
	VulkanLogicalDevice *_dev;
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
	UniformBufferBinding(VulkanLogicalDevice *dev,int binding, int nElems, std::vector<VkShaderStageFlagBits> stages,GPUMemoryType memType)
	{
		assert(nElems > 0);

		_dev = dev;
		_ubo.binding = binding;
		_ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		_ubo.descriptorCount = 1;
		_ubo.pImmutableSamplers = nullptr;
		_ubo.stageFlags = ArrayFunctions::FromBitFlagsToInt(stages);

		_memoryType = memType;
		_data.resize(nElems);

		_buffer = new VulkanMappedBuffer<T>()
		//createBuffer(sizeof(Data), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory)
	}

	virtual void Load(IVulkanResourceLoadContext *context) override {
		
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
	virtual void Clear() override
	{
		_dirty = false;
	}
	virtual GPUMemoryType MemoryType() override
	{
		return _memoryType;
	}

};

