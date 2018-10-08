#pragma once
#include <MGLEngine.Shared/Interfaces/ISerializable.h>
#include <MGLEngine.Shared/Interfaces/ITopology3D.h>
#include <MGLEngine.Shared/Window/ICanvas.h>

class IShapeHandle;

class IShape3D : ISerializable
{
public:
	IShape3D();
	~IShape3D();
	virtual IShapeHandle* Draw(ICanvas *canvas, ITopology3D *top) = 0;
	
};

