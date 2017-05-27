#pragma once
#include "../../Shapes/ITopology2D.h"
#include "../../Shapes/IRender2D.h"
#include "../Exception.h"
struct ArrayLocation
{
	size_t OffI;
	size_t SizeI;
	size_t OffV;
	size_t SizeV;
};


enum DrawInfoType {Root,Shape,Batch};
template <class VerticeData>
class ShapeInfo
{
	public:
		ITopology2D *Topology;
		IRender2D<VerticeData> *Render;


};

template<class VerticeData>
class DrawInfo
{
	ShapeInfo<VerticeData> _shape;
	DrawInfo()
	{
		*this = {};
		NeedRedraw = true;
	}
	
public:
	
	ArrayLocation Current;
	ArrayLocation Future;
	DrawInfoType DrawInfoType;
	bool NeedRedraw;
	
	bool IsRoot() const { return DrawInfoType == Root; }
	bool IsBatch() const  { return DrawInfoType == Batch; }
	bool IsShape() const { return DrawInfoType == Shape; }


	ShapeInfo<VerticeData>& GetShape()
	{
		if (DrawInfoType==Shape)  
			return _shape;
		else
			throw new Exception("DrawInfo Node is not a shape");
	}

	static DrawInfo<VerticeData> CreateRoot()
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Root;
		return info;
	}
	
	~DrawInfo() {}

};

