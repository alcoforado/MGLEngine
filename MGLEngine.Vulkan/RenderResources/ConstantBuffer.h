#pragma once
#include <MGLEngine.Shared/Utils/DrawTree/IRenderResource.h>
#include "MGLEngine.Vulkan/Shaders/IVulkanRenderContext.h"
#include <MGLEngine.Shared/Utils/Arrays/ArrayFunctions.h>
#include "IVulkanRenderResource.h"

template<class Data>
class ConstantBuffer : public IRenderResource,IVulkanRenderResource
{
	Data _data;
	bool _dirty;
	VkBuffer _buffer;
	VkDeviceMemory _bufferMemory;


public:
	ConstantBuffer(int binding, std::vector<VkShaderStageFlagBits> stages)
	{
		VkDescriptorSetLayoutBinding ubo = {};
		ubo.binding = 0;
		ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubo.descriptorCount = 1;
		ubo.pImmutableSamplers = nullptr;
		
		int r = ArrayFunctions::FromBitFlagsToInt(stages);
		ubo.stageFlags = r;

		createBuffer(sizeof(Data), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory)
	}

	virtual ~ConstantBuffer()
	{
		
	}
	virtual bool Compatible(IRenderResource *res)
	{
		return res == this;
	}
	virtual void SetData(Data data)
	{
		this->_data = data;
		this->_dirty = true;
	}


};

