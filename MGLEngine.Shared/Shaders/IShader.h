#pragma once
#include <MGLEngine.Shared/Interfaces/IPainter.h>
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>

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
	virtual IShapeHandle* Add(ITopology2D *topology, IPainter<VerticeData> *render) = 0;
};

