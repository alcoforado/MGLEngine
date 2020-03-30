#pragma once
#include <MGLEngine.Shared/Interfaces/IShaderDataWriter.h>
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include <MGLEngine.Shared/Interfaces/IShapeHandle.h>


template<class VerticeData>
class IShader2D
{
public:
	virtual ~IShader2D(){}
	virtual IShapeHandle* Add(ITopology2D *topology, IShaderDataWriter<VerticeData> *render) = 0;
};

