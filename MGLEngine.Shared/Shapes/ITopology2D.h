#pragma once
class ITopology2D
{
public:
	virtual size_t NVertices()=0;
	virtual size_t NIndices()=0;

	virtual void WriteTopology(SubArray &array)
	{
		
	}

	ITopology2D();
	~ITopology2D();
};

