#pragma once
#include "../../Shapes/ITopology2D.h"
#include "../../Shapes/ITopology3D.h"
#include "../Exception.h"
#include "../../Shapes/IRender.h"
#include <assert.h>
struct ArrayLocation
{
	Index OffI;
	Index SizeI;
	Index OffV;
	Index SizeV;

	ArrayLocation()
	{
		OffI = OffV = 0;
		SizeI = SizeV = 0;
	}
};


enum DrawInfoType { Root, Shape, Batch };



template<class VerticeData>
class ShapeInfo
{
	ITopology2D *_topology2D;
	IRender<VerticeData> *_render;
public:

	
	void WriteData(IArray<VerticeData> &v, Indices &i)
	{
		assert(_topology2D != nullptr);
		assert(_render != nullptr);


			ArraySelect<glm::vec2> sV(v, &VerticeData::Position);
			_topology2D->WriteTopology(sV, i);
			_render->Write(v);
	}

	Index NVertices()
	{
		return _topology2D->NVertices();
	}
	Index NIndices()
	{
		return _topology2D->NIndices();
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
	bool IsBatch() const { return DrawInfoType == Batch; }
	bool IsShape() const { return DrawInfoType == Shape; }


	ShapeInfo<VerticeData>& GetShape()
	{
		if (DrawInfoType == Shape)
			return _shape;
		else
			throw new Exception("DrawInfo Node is not a shape");
	}

	void RedrawShape(IArray<VerticeData> &vertices, Indices &indices)
	{
		assert(IsShape());
		assert(vertices.size() >= Future.OffV + Future.SizeV);
		IArray<VerticeData> arrayV(vertices.data() + Future.OffV, Future.SizeV);
		Indices arrayI(indices.GetPointer() + Future.OffI, this->Future.SizeI);
		GetShape().WriteData(arrayV, arrayI);
		for (long unsigned i = 0; i < arrayI.size(); i++)
		{
			arrayI[i] += this->Future.OffI;
		}

	}


	static DrawInfo<VerticeData> CreateShape(ITopology2D *top, IRender<VerticeData> *render)
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Shape;
		info._shape.Topology = top;
		info._shape._render = render;
	}


	static DrawInfo<VerticeData> CreateRoot()
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Root;
		return info;
	}

	~DrawInfo() {}

};

