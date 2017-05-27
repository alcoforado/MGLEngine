#pragma once
template<class VerticeData>
class IRender2D
{

public:
	IRender2D() {}
	~IRender2D() {}
	virtual void Write(IArray<VerticeData> &array) = 0;
};


