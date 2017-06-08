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


enum DrawInfoType {Root,Shape,Batch};

template <class VerticeData,int dim>
class ShapeInfo
{
	public:
	
};


template<class VerticeData>
class ShapeInfo<VerticeData,2>
{
public:
	ITopology2D *Topology;
	IRender<VerticeData> *Render;
	void WriteData(IArray<VerticeData> &v, Indices &i)
	{
		assert(Topology != nullptr);
		assert(Render != nullptr);
		ArraySelect<glm::vec2> sV(v, &VerticeData::Position);
		Topology->WriteTopology(sV, i);
		Render->Write(v);
	}
};


template<class VerticeData>
class ShapeInfo<VerticeData, 3>
{
public:
	ITopology3D *Topology;
	IRender<VerticeData> *Render;
	void WriteData(IArray<VerticeData> &v, Indices &i)
	{
		assert(Topology != nullptr);
		assert(Render != nullptr);
		ArraySelect<glm::vec3> sV(v, &VerticeData::Position);
		Topology->WriteTopology(sV, i);
		Render->Write(v);
	}
};





template<class VerticeData,int dim>
class DrawInfo
{
	ShapeInfo<VerticeData,dim> _shape;
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


	DrawInfo(const DrawInfo<VerticeData,dim>& data)
	{
		*this = data;
	}
	
	
	bool IsRoot() const { return DrawInfoType == Root; }
	bool IsBatch() const  { return DrawInfoType == Batch; }
	bool IsShape() const { return DrawInfoType == Shape; }


	ShapeInfo<VerticeData,dim>& GetShape()
	{
		if (DrawInfoType==Shape)  
			return _shape;
		else
			throw new Exception("DrawInfo Node is not a shape");
	}

	void RedrawShape(IArray<VerticeData> &vertices, Indices &indices)
	{
		assert(IsShape());
		assert(vertices.size() >= Future.OffV+Future.SizeV);
		IArray<VerticeData> arrayV(vertices.data()+Future.OffV,Future.SizeV );
		Indices arrayI(indices.GetPointer() + Future.OffI, this->Future.SizeI);
		GetShape().WriteData(arrayV, arrayI);
		for (long unsigned i = 0; i < arrayI.size(); i++)
		{
			arrayI[i] += this->Future.OffI;
		}
		
	}


	static DrawInfo<VerticeData,dim> CreateShape(ITopology2D *top,IRender<VerticeData> *render)
	{
		DrawInfo<VerticeData,dim> info;
		info.DrawInfoType = Shape;
		info._shape.Topology = top;
		info._shape.Render = render;
	}


	static DrawInfo<VerticeData,dim> CreateRoot()
	{
		DrawInfo<VerticeData,dim> info;
		info.DrawInfoType = Root;
		return info;
	}
	
	~DrawInfo() {}

};

