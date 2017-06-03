#pragma once

#include "Utils/Arrays/IArray.h"
template<class VerticeData>
class IRender
{

public:
	IRender(){}
	virtual ~IRender(){}
	virtual void Write(IArray<VerticeData> &array)=0;
};

