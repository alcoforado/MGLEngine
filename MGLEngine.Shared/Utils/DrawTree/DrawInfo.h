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
	
	
public:
	DrawInfo(const DrawInfo<VerticeData>& data)
	{
		*this = data;
	}
	DrawInfo()
	{
		*this = CreateRoot();
	}

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
	static DrawInfo<VerticeData> CreateShape(ITopology2D *top,IRender2D<VerticeData> *render)
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

