#pragma once
#include <MGLEngine.Shared/Utils/DrawTree/IResource.h>

template<class Data>
class ConstantBuffer : public IResource
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

