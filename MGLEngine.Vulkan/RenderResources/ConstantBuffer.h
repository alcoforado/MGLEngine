#pragma once
#include <MGLEngine.Shared/Utils/DrawTree/IRenderResource.h>
#include "MGLEngine.Vulkan/Shaders/IVulkanRenderContext.h"

template<class Data>
class ConstantBuffer : public IRenderResource
{
	Data _data;
public:
	ConstantBuffer();
	virtual ~ConstantBuffer()
	{
		
	}
	virtual bool Compatible(IResource *res)
	{
		
	}
	virtual void SetData(Data data)
	{
		this->_data = data;
	}
};

