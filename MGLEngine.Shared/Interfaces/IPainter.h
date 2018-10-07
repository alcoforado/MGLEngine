#pragma once

#include <MGLEngine.Shared/Utils/Arrays/IArray.h>
template<class VerticeData>
class IPainter 
{

public:
	IPainter(){}
	virtual ~IPainter(){}
	virtual void Write(IArray<VerticeData> &array)=0;
	//virtual void Draw(ITopology2D *top)=0;

};
