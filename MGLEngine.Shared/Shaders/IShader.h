#pragma once
#include <MGLEngine.Shared/Shapes/IRender.h>
#include <MGLEngine.Shared/Shapes/ITopology2D.h>
template<class VerticeData>
class IShader
{
public:
	virtual ~IShader(){}
	virtual void Add(ITopology2D *topology, IRender<VerticeData> *render) = 0;
};

