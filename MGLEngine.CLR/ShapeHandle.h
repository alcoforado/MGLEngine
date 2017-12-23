#pragma once

class IShapeHandle;
namespace MGLEngineCLR{
public ref class ShapeHandle
{
	IShapeHandle *_shapeHandle;
public:
	ShapeHandle(IShapeHandle *handle)
	{
		_shapeHandle = handle;
	}
	void Delete();


};
}
