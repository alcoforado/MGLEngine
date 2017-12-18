#pragma once
#include "DrawInfo.h"
#include "../NTree.h"
#include "../DefragArray/CopyRegion.h"
#include "../Arrays/IArray.h"
#include "../DefragArray/DefragArray.h"
#include <MGLEngine.Shared/Shaders/IShader.h>

template<class VerticeData>
class DrawTree : public  IShader<VerticeData>
{
	NTreeNode<DrawInfo<VerticeData>> _root;
	
	class ShapeHandle
	{
		NTreeNode<DrawInfo<VerticeData>> *_node;
	public:

		ShapeHandle(NTreeNode<DrawInfo<VerticeData>> *node)
		{
			assert(node);
			assert(_node->GetData().IsShape());
			_node = node;
		}

		virtual void Delete()
		{
			if (_node == nullptr)
			{
				throw new Exception("Shape Handle was already deleted");
			}
			_node->CutSubTree();
			delete _node;
			_node = nullptr;
		}


	};


public:
	 
	class IShapeHhandle
	{
	public:
		virtual void Delete() = 0;
	};



	typedef VerticeData VerticeType;

	DrawTree()
		:_root(DrawInfo<VerticeData>::CreateRoot())
	{


	}

	bool NeedRedraw()
	{
		return _root.GetData().NeedRedraw;
	}
	NTreeNode<DrawInfo<VerticeData>>* GetRoot() { return &_root; }


	void ComputeSizes()
	{
		int offI = 0;
		int offV = 0;
		_root.ForAllInOrder([&](NTreeNode<DrawInfo<VerticeData>>* pNode) {
		
			DrawInfo<VerticeData>& info = pNode->GetData();
			info.Current = info.Future;
			if (info.IsShape())
			{
				
				ShapeInfo<VerticeData> &shape = info.GetShape();
				info.Future.SizeI = shape.NIndices();
				info.Future.SizeV = shape.NVertices();
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
					info.Future.OffV= pNode->GetChilds().front()->GetData().Future.OffV;
					info.Future.OffI= pNode->GetChilds().front()->GetData().Future.OffI;
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

	

	void UpdateVerticeData(IArray<VerticeData> &vertices, Indices &indices)
	{
		
		if (!_root.GetData().NeedRedraw)
			return;
		
		/*
		 * If the vertices, indices have to be expanded beyond their maximum capacity  throw exception.
		 * In this case we need to use  the other  UpdateVerticeData  or the  full  sync.
		 */
		if (_root.GetData().Future.SizeI > indices.capacity() || _root.GetData().Future.SizeV > vertices.capacity())
		{
			throw new Exception("Error, the vertices and/or indices need to be expanded  beyond their capacity.\n Use FullRewrite method or the update vertices overload where you pass another vertice/indices vector pair with the right size");
		}
		


		//To contain which regions we should copy
		std::vector<CopyRegion> copiesV,copiesI;
		std::list<DrawInfo<VerticeData>*> shapesToRedraw;
		_root.ForAllPreOrderControlDescent([&](NTreeNode<DrawInfo<VerticeData>>* pNode)->bool {
			DrawInfo<VerticeData>& info = pNode->GetData();
			if (info.NeedRedraw)
			{
				if (info.IsShape())
				{
					shapesToRedraw.push_back(&info);
					
					return true;
				}
				else {
					//For all nodes	
					info.NeedRedraw = false; //Set this node as processed
					info.Current = info.Future;//Past Dimensions are update with the Current Dimension
					return true; //descend to the childs if they exist.
				}
			}
			else
			{

				//if the alghorithm reached a non changed shape, it means one of its siblings shapes changed.
				//In this case update the offsets. 
				//If it is a batch we also have to update all offsets of all the indices in the batch
				Indices vI(indices.GetPointer() + info.Current.OffI, info.Current.SizeI);
				vI.AdjustArray(info.Current.OffI, info.Future.OffI);

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

		
		//remember IArray resize don't allocate more memory.
		//It can only grow up to capacity of the array
		//the old contents of the array are still present
		vertices.Resize(_root.GetData().Future.SizeV);
		indices.Resize(_root.GetData().Future.SizeI);


		DefragArray defrag;
		defrag.ReorganizeArray(vertices, copiesV);
		defrag.ReorganizeArray(indices, copiesI);

		//All the copies are done, redraw the pending shapes
		for (auto info : shapesToRedraw)
		{
			info->RedrawShape(vertices,indices);
			info->NeedRedraw = false; //Set this node as processed
			info->Current = info->Future;//Past Dimensions are update with the Current Dimension
		}

	}


	void UpdateVerticeData(
		IArray<VerticeData> &vertices , Indices  &indices,
		IArray<VerticeData> &oVertices, Indices  &oIndices)
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

		_root.ForAllPreOrderControlDescent([&](NTreeNode<DrawInfo<VerticeData>>* pNode)->bool {
			DrawInfo<VerticeData>& info = pNode->GetData();
			if (info.NeedRedraw)
			{
				if (info.IsShape())
				{
					info.RedrawShape(oVertices,oIndices);
				}
				//For all nodes	
				info.NeedRedraw = false; //Set this node as processed
				info.Current = info.Future;//Past Dimensions are update with the Current Dimension
				return true; //descend to the childs if they exist.
			}
			else
			{
				
					//if the alghorithm reached a non changed shape, it means one of its siblings shapes changed.
					//In this case update the offsets. 
					//If it is a batch we also have to update all offsets of all the indices in the batch
					Indices vI(oIndices.GetPointer() + info.Current.OffI, info.Current.SizeI);
					vI.AdjustArray(info.Current.OffI, info.Future.OffI);
				


				//Node needs to have its data copied
				copiesV.push_back(CopyRegion(
					ArrayRegion(info.Current.OffV, info.Current.SizeV),
					ArrayRegion(info.Future.OffV, info.Future.SizeV)
				));
				copiesI.push_back(CopyRegion(
					ArrayRegion(info.Current.OffI, info.Current.SizeI),
					ArrayRegion(info.Future.OffI, info.Future.SizeI)
				));
				//Fix the Offset


				//Remember, when we set the NeedRedraw=true of a node, the draw tree set the needdraw=true to all its parents.
				//If the node does not need redraw, neither does any of its childs.
				//Don't need to go deeper in the tree.
				return false;
			}
		});

		DefragArray defrag;
		defrag.ReorganizeArray(vertices,oVertices, copiesV);
		defrag.ReorganizeArray(indices, oIndices,copiesI);
	}









	virtual IShapeHandle Add(ITopology2D *topology,IRender<VerticeData> *render) override 
	{
		DrawInfo<VerticeData> data = DrawInfo<VerticeData>::CreateShape(topology, render);
		auto node = new NTreeNode<DrawInfo<VerticeData>>(data);
		_root.AppendChild(node);
		
		node->ForItselfAndAllParents([](NTreeNode<DrawInfo<VerticeData>>* pNode)->void {
			pNode->GetData().NeedRedraw = true;
		});


	}

	~DrawTree(){}
};

