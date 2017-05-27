#pragma once
class PositionArray2D
{
public:
	size_t _size;

	void* _p;

	template<class VerticeData>
	PositionArray2D(VerticeData *p,size_t size)
	{
		_p = p;
		_size = size;
	}
	~PositionArray2D();
};

