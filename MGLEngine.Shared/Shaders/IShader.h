#pragma once
#include "..\Shapes\IT
#include "MGLEngine.Shared/Shapes/IRender.h"

template<class VerticeData>
class IShader
{
public:
	virtual ~IShader(){}
	virtual void Add(ITopology2D *topology, IRender<VerticeData> *render) = 0;
};

