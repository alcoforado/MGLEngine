#pragma once
#include "DrawInfo.h"
#include "../NTree.h"
#include "../DefragArray/CopyRegion.h"
#include "../Arrays/IArray.h"
#include "../DefragArray/DefragArray.h"
template<class VerticeData>
class DrawTree
{
	NTreeNode<DrawInfo<VerticeData>> _root;
	
	
public:

	DrawTree()
		:_root(DrawInfo<VerticeData>::CreateRoot())
	{
		
		
	}





	void ComputeSizes()
	{
		int offI = 0;
		int offV = 0;
		_root.ForAllInOrder([](NTreeNode<DrawInfo<VerticeData>>* pNode) {
		
			DrawInfo<VerticeData>& info = pNode->GetData();
			info.Current = info.Future;
			if (info.IsShape())
			{
				
				ShapeInfo<VerticeData> &shape = info.GetShape();
				info.Future.SizeI = shape.Topology.NIndices();
				info.Future.SizeV = shape.Topology.NVertices();
				info.Future.OffI = offI;
				info.Future.OffV = offV;
				
				offI += info.Future.SizeI;
				offV += info.Future.SizeV;
			}
			if (info.IsBatch())
			{
				
				info.Future.SizeI = 0;
				info.Future.SizeV = 0;
				for(NTreeNode<DrawInfo<VerticeData>>* child : pNode->GetChilds())
				{
					info.Future.SizeI += child->GetData().Future.SizeI;
					info.Future.SizeV += child->GetData().Future.SizeV;
				}
				if (pNode->GetChilds().size() != 0)
				{
					info.OffV= pNode->GetChilds().front().GetData().Future.OffV;
					info.OffI= pNode->GetChilds().front().GetData().Future.OffI;
				}
			}
			if (info.IsRoot())
			{
				info.Future.SizeI = info.Future.SizeV = 0;
				for (NTreeNode<DrawInfo<VerticeData>>* child : pNode->GetChilds())
				{
					info.Future.SizeI += child->GetData().Future.SizeI;
					info.Future.SizeV += child->GetData().Future.SizeV;
				}
				info.Future.OffI = 0;
				info.Future.OffV = 0;
			}
		});
	}

	

	void UpdateVerticeData(IArray<VerticeData> &vertices, IArray<unsigned> &indices)
	{
		
		if (!_root.GetData().NeedRedraw)
			return;
		
		/*
		 * If the vertices, indices have to be expanded beyond their maximum capacity  throw exception.
		 * In this case we need to use  the other  UpdateVerticeData  or the  full  sync.
		 */
		if (_root.GetData().Future.SizeI > indices.capacity() || _root.GetData().Future.SizeV > vertices.capacity())
		{
			throw new Exception("Error, the vertices and/or indices need to be expanded  beyond their capacity.\n Use FullRewrite method or the update vertices overload where you pass another vertice/indices vector pair with the right size")
			
		}
		
		//To contain which regions we should copy to dst vector
		std::vector<CopyRegion> copiesV,copiesI;

		_root.ForAllPreOrderControlDescent([](NTreeNode<DrawInfo<VerticeData>>* pNode)->bool {
			DrawInfo<VerticeData>& info = pNode->GetData();
			if (info.NeedRedraw)
			{
				if (info.IsShape())
				{
					assert(pDstV->size() >= info.Future.OffV+info.Future.SizeV);
					IArray<VerticeData> arrayV(vertices.GetPointer()+info.Future.OffV,info.Future.SizeV );
					IArray<uint32_t> arrayI(indices.GetPointer() + info.Future.OffI, info.Future.SizeI);
					info.GetShape().WriteData(arrayV, arrayI);

				}
				//For all nodes	
				info.NeedRedraw = false; //Set this node as processed
				info.Current = info.Future;//Past Dimensions are update with the Current Dimension
				return true; //descend to the childs if they exist.
			}
			else
			{
				//Node needs to have its data copied
				copiesV.push_back(CopyRegion(
					ArrayRegion(info.Current.OffV, info.Current.SizeV),
					ArrayRegion(info.Future.OffV,info.Future.SizeV)
				));
				copiesI.push_back(CopyRegion(
					ArrayRegion(info.Current.OffI, info.Current.SizeI),
					ArrayRegion(info.Future.OffI, info.Future.SizeI)
				));
				//Remember, when we set the NeedRedraw=true of a node, the draw tree set the needdraw=true to all its parents.
				//If the node does not need redraw, neither does any of its childs.
				//Don't need to go deeper in the tree.
				return false;
			}
		});

		DefragArray<VerticeData> defrag;
		defrag.ReorganizeArray(vertices, copiesV);
		defrag.ReorganizeArray(indices, copiesI);
	}


	void UpdateVerticeData(
		IArray<VerticeData> &vertices , IArray<unsigned>  &indices,
		IArray<VerticeData> &oVertices, IArray<unsigned>  &oIndices)
	{

		if (!_root.GetData().NeedRedraw)
			return;

		/*
		* If the vertices, indices have to be expanded allocate another vector.
		* The shapes that need redraw, will write to these new vectors, the other shapes will have their data copied over.
		*/
		if (_root.GetData().Future.SizeI > oIndices.capacity() || _root.GetData().Future.SizeV > oVertices.capacity())
		{
			throw new Exception("The vertices/indices arrays don't have enough capacity to redraw. Call updateverticesdata with an extra pair of vertices/indices vectors to contain the new vertices, arrays");
		}
		
		//To contain which regions we should copy to dst vector
		std::vector<CopyRegion> copiesV, copiesI;

		_root.ForAllPreOrderControlDescent([](NTreeNode<DrawInfo<VerticeData>>* pNode)->bool {
			DrawInfo<VerticeData>& info = pNode->GetData();
			if (info.NeedRedraw)
			{
				if (info.IsShape())
				{
					assert(vertices.size() >= info.Future.OffV + info.Future.SizeV);
					IArray<VerticeData> arrayV(oVertices.GetPointer() + info.Future.OffV, info.Future.SizeV);
					IArray<uint32_t> arrayI(oIndices.GetPointer() + info.Future.OffI, info.Future.SizeI);
					info.GetShape().WriteData(arrayV, arrayI);
				}
				//For all nodes	
				info.NeedRedraw = false; //Set this node as processed
				info.Current = info.Future;//Past Dimensions are update with the Current Dimension
				return true; //descend to the childs if they exist.
			}
			else
			{
				//Node needs to have its data copied
				copiesV.push_back(CopyRegion(
					ArrayRegion(info.Current.OffV, info.Current.SizeV),
					ArrayRegion(info.Future.OffV, info.Future.SizeV)
				));
				copiesI.push_back(CopyRegion(
					ArrayRegion(info.Current.OffI, info.Current.SizeI),
					ArrayRegion(info.Future.OffI, info.Future.SizeI)
				));
				//Remember, when we set the NeedRedraw=true of a node, the draw tree set the needdraw=true to all its parents.
				//If the node does not need redraw, neither does any of its childs.
				//Don't need to go deeper in the tree.
				return false;
			}
		});

		DefragArray<VerticeData> defrag;
		defrag.ReorganizeArray(vertices,oVertices, copiesV);
		defrag.ReorganizeArray(indices, oIndices,copiesI);
	}









	void Add(ITopology2D *topology,IRender<VerticeData> *render)
	{
		auto node = new NTreeNode<VerticeData>(DrawInfo<VerticeData>(topology, render));
		_root.AppendChild(node);
	}

	~DrawTree(){}
};

