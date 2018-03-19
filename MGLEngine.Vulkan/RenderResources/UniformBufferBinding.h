#pragma once
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>
#include "MGLEngine.Vulkan/Shaders/IVulkanRenderContext.h"
#include <MGLEngine.Shared/Utils/Arrays/ArrayFunctions.h>
#include "IVulkanRenderResource.h"
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>
template<class Data>
class UniformBufferBinding : public IVulkanRenderResource
{
	std::vector<Data> _data;
	bool _dirty;
	VkBuffer _buffer;
	VkDeviceMemory _bufferMemory;
	GPUMemoryType _memoryType;
	VkDescriptorSetLayoutBinding _ubo = {};

private:
	virtual void UpdateDescriptorSet(VulkanDescriptorSet *dsSet)
	{
		VkDescriptorBufferInfo bufferInfo;
		bufferInfo.buffer = _buffer;
		bufferInfo.offset = 0;
	//	bufferInfo.range=
		dsSet->GetDescriptorSetHandle();
	}


public:
	UniformBufferBinding(int binding, int nElems, std::vector<VkShaderStageFlagBits> stages,GPUMemoryType memType)
	{
		assert(nElems > 0);
		_ubo.binding = binding;
		_ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		_ubo.descriptorCount = 1;
		_ubo.pImmutableSamplers = nullptr;
		_ubo.stageFlags = ArrayFunctions::FromBitFlagsToInt(stages);

		_memoryType = memType;
		_data.resize(1);
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

