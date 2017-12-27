#pragma once
#include <MGLEngine.Shared/Shapes/IRender.h>
#include <MGLEngine.Shared/Shapes/ITopology2D.h>

class IShapeHandle
{
public:
	virtual void Delete() = 0;
	virtual ~IShapeHandle(){}
};


template<class VerticeData>
class IShader
{
public:
	virtual ~IShader(){}
	virtual IShapeHandle* Add(ITopology2D *topology, IRender<VerticeData> *render) = 0;
};

