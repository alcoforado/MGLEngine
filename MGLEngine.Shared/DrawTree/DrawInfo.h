#pragma once
#include <MGLEngine.Shared/Interfaces/ITopology2D.h>
#include <MGLEngine.Shared/Interfaces/ITopology3D.h>
#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Shared/Interfaces/IShaderDataWriter.h>
#include <type_traits>
#include <assert.h>
#include <MGLEngine.Shared/DrawTree/IRenderResource.h>

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

public:
	static constexpr const bool Is3D = std::is_same<decltype(VerticeData::Position), glm::vec3>::value;
	typedef typename std::conditional<Is3D, ITopology3D, ITopology2D>::type TopologyType;
	
private:	
	std::shared_ptr<TopologyType> _topology;
	std::shared_ptr<IShaderDataWriter<VerticeData>> _render;
public:

	ShapeInfo(std::shared_ptr<TopologyType> topology,std::shared_ptr<IShaderDataWriter<VerticeData>> render)
	{
		_topology = topology;
		_render = render;
	}

	ShapeInfo()
	{
		_topology = nullptr;
		_render = nullptr;
	}

	template<class T=VerticeData>
	typename std::enable_if<!std::is_same<decltype(T::Position), glm::vec3>::value,void>::type WriteData(IArray<VerticeData> &v, Indices &i)
	{
		assert(_topology != nullptr);
		assert(_render != nullptr);


		ArraySelect<glm::vec2> sV(v, &VerticeData::Position);
		_topology->WriteTopology(sV, i);
		_render->Write(v);
	}

	template<class T = VerticeData>
	typename std::enable_if<std::is_same<decltype(T::Position), glm::vec3>::value, void>::type WriteData(IArray<VerticeData> &v, Indices &i)
	{
		assert(_topology != nullptr);
		assert(_render != nullptr);


		ArraySelect<glm::vec3> sV(v, &VerticeData::Position);
		_topology->WriteTopology(sV, i);
		_render->Write(v);
	}

	TOPOLOGY_TYPE GetTopologyType()
	{
		eassert(_topology != nullptr, "Topology is not set");
		return _topology->GetTopologyType();
		
	}

	Index NVertices()
	{
		eassert(_topology != nullptr, "Topology is not set");
		return _topology->NVertices();
	}
	Index NIndices()
	{
		eassert(_topology != nullptr, "Topology is not set");
		return _topology->NIndices();
	}

};






template<class VerticeData>
class DrawInfo
{
	ShapeInfo<VerticeData> _shape;
	DrawInfo()
	{
		NeedRedraw = true;
		DrawInfoType = Root;
	}

	std::list<IRenderResource*> Resources;
	TOPOLOGY_TYPE _batchTopologyType;

public:
	ArrayLocation Current;
	ArrayLocation Future;
	DrawInfoType DrawInfoType;
	bool NeedRedraw;
	

	DrawInfo(const DrawInfo<VerticeData>& data)
	{
		*this = data;
	}
	const std::list<IRenderResource*>& GetResources()
	{
		return Resources;
	}

	TOPOLOGY_TYPE GetTopology()
	{
		if (IsBatch())
			return _batchTopologyType;
		if (IsShape())
			return _shape.GetTopologyType();
		eassert(false, "Trying to get topology of a root node");
	}


	bool HasDirtyResources()
	{
		
		for(auto r : this->Resources)
		{
			if (r->IsDirty())
				return true;
		}
		return false;
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


	static DrawInfo<VerticeData> CreateShape(std::shared_ptr<typename ShapeInfo<VerticeData>::TopologyType> top, std::shared_ptr<IShaderDataWriter<VerticeData>> render)
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Shape;
		info._shape = ShapeInfo<VerticeData>(top,render);
		return info;
	}

	static DrawInfo<VerticeData> CreateShape(typename ShapeInfo<VerticeData>::TopologyType *top, IShaderDataWriter<VerticeData> *render)
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Shape;
		info._shape = ShapeInfo<VerticeData>(std::shared_ptr<typename ShapeInfo<VerticeData>::TopologyType>(top) , std::shared_ptr<IShaderDataWriter<VerticeData>>(render));
		return info;
	}

	static DrawInfo<VerticeData> CreateRoot()
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Root;
		info.NeedRedraw = true;

		return info;
	}
	
	static DrawInfo<VerticeData> CreateBatch(TOPOLOGY_TYPE topType)
	{
		DrawInfo<VerticeData> info;
		info.DrawInfoType = Batch;
		info.NeedRedraw = true;
		info._batchTopologyType = topType;


		return info;
	}



	~DrawInfo() {}

};

