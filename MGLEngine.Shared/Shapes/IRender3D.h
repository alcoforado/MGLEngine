#pragma once
template<class VerticeData>
class IRender3D
{

public:
	IRender3D(){}
	~IRender3D(){}
	virtual void Write(IArray<VerticeData> &array)=0;
};

