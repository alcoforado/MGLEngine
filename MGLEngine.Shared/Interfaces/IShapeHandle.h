#pragma once
class IShapeHandle
{
public:
	virtual void Delete() = 0;
	virtual ~IShapeHandle() {}
};

