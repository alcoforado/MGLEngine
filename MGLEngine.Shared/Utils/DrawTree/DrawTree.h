#pragma once
#include "DrawInfo.h"
#include "../NTree.h"

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

	void Draw()
	{
		



	}


	~DrawTree();
};

