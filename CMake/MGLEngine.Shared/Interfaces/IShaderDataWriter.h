#pragma once

#include <MGLEngine.Shared/Utils/Arrays/IArray.h>
template<class VerticeData>
class IShaderDataWriter 
{

public:
	IShaderDataWriter(){}
	virtual ~IShaderDataWriter(){}
	virtual void Write(IArray<VerticeData> &array)=0;
	

};

