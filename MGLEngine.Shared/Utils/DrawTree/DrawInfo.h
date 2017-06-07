#pragma once
#include "../../Shapes/ITopology2D.h"
#include "../Exception.h"
#include "../../Shapes/IRender.h"
struct ArrayLocation
{
	uint32_t OffI;
	uint32_t SizeI;
	uint32_t OffV;
	uint32_t SizeV;
	
	ArrayLocation()
	{
		OffI = SizeI = OffV = SizeV = 0;
	}
};


enum DrawInfoType {Root,Shape,Batch};
template <class VerticeData>
class ShapeInfo
{
	public:
		ITopology2D *Topology;
		IRender<VerticeData> *Render;
		void WriteData(IArray<VerticeData> &v,IArray<uint32_t> &i)
		{
			assert(Topology != nullptr);
			assert(Render != nullptr);
			ArraySelect<glm::vec2> sV(v, &VerticeData::Position);
			Topology->WriteTopology(sV, i);
			Render->Write(v);
		}
};

template<class VerticeData>
class DrawInfo
{
	ShapeInfo<VerticeData> _shape;
	DrawInfo()
	{
		NeedRedraw = false;
		DrawInfoType = Root;
	}

	

public:
	ArrayLocation Current;
	ArrayLocation Future;
	DrawInfoType DrawInfoType;
	bool NeedRedraw;


	DrawInfo(const DrawInfo<VerticeData>& data)
	{
		*this = data;
	}
	
	
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
	static DrawInfo<VerticeData> CreateShape(ITopology2D *top,IRender<VerticeData> *render)
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Shape;
		info._shape.Topology = top;
		info._shape.Render = render;
	}


	static DrawInfo<VerticeData> CreateRoot()
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Root;
		return info;
	}
	
	~DrawInfo() {}

};

