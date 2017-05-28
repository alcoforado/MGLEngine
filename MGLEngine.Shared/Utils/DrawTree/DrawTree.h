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
	std::vector<VerticeData> vertices;
	std::vector<uint32_t> indices;
	
	
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

	void WriteVerticeData()
	{
		
		if (!_root.GetData().NeedRedraw)
			return;
		
		ComputeSizes();
		std::vector<uint32_t> dstI, *pDstI;
		std::vector<VerticeData> dstV,*pDstV;
		/*
		 * If the vertices, indices have to be expanded allocate another vector.
		 * The shapes that need redraw, will write to these new vectors, the other shapes will have their data copied over.
		 */
		if (_root.GetData().Future.SizeI > indices.capacity() || _root.GetData().Future.SizeV > vertices.capacity())
		{
			dstI.reserve(_root.GetData().Future.SizeI + _root.GetData().Future.SizeI / 5);
			dstI.resize(_root.GetData().Future.SizeI);
			dstV.reserve(_root.GetData().Future.SizeV + _root.GetData().Future.SizeV / 5);
			dstV.resize(_root.GetData().Future.SizeV);
			pDstI = &dstI;
			pDstV = &dstV;
		}
		else
		{
			//Destine vectors and src are one and the same.
			pDstI = &indices;
			pDstV = &vertices;
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
					IArray<VerticeData> arrayV(pDstV->data()+info.Future.OffV,info.Future.SizeV );
					IArray<uint32_t> arrayI(pDstI->data() + info.Future.OffI, info.Future.SizeI);
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
		if (dstV.size() !=0)
		{
			//Src and destiny does not share the same vector.
			defrag.ReorganizeArray(vertices, dstV, copiesV);
			defrag.ReorganizeArray(indices, dstI, copiesI);
			dstV.swap(vertices);
			dstI.swap(indices);
		}
		else
		{
			defrag.ReorganizeArray(vertices, copiesV);
			defrag.ReorganizeArray(indices, copiesI);
		}


	}
	void Add(ITopology2D *topology,IRender2D<VerticeData> *render)
	{
		auto node = new NTreeNode<VerticeData>(DrawInfo<VerticeData>(topology, render));
		_root.AppendChild(node);
	}

	~DrawTree(){}
};

