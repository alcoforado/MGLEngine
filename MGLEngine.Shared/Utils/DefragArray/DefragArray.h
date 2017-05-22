#pragma once
#include "CopyRegion.h"
#include "../opointer.h"
#include <vector>
#include <list>
#include "CopyPlanSequenceDetail.h"

template<class T>
class DefragArray
{
public:
	std::vector<CopyRegion>* OptimizePlan(std::vector<CopyRegion> p)
	{
		
		std::sort(p.begin(), p.end(), [](const CopyRegion &a, const CopyRegion &b)->bool
		{
			return a.Orig.offI < b.Orig.offI;
		});



		std::vector<CopyRegion>* optimumPlan = new std::vector<CopyRegion>();
		optimumPlan->reserve(p.size());

		if (p.size() > 1)
		{
			CopyRegion rg = p[0];
			for (int i = 1; i < p.size(); i++)
			{
				if (!rg.TryRightMerge(p[i]))
				{
					optimumPlan->push_back(rg);
					rg = p[i];
				}
			}
			optimumPlan->push_back(rg);
		}
		else
		{
			optimumPlan->push_back(p[0]);
		}
		return optimumPlan;
	}
	/*
	public static void CopyArraySegments<T>(T[] src, T[] dst, List<CopyPlan> plan)
	{
		var optPlan = OptimizePlan(plan);
		foreach(var cp in optPlan)
		{
			CopyArraySegment(src, dst, cp);
		}
	}

	public static void CopyArraySegment<T>(T[] src, T[] dst, CopyPlan cp)
	{
		System.Diagnostics.Debug.Assert(cp.Dst.size >= cp.Orig.size);
		System.Diagnostics.Debug.Assert(cp.Orig.offI + cp.Orig.size <= src.Length);
		System.Diagnostics.Debug.Assert(cp.Dst.offI + cp.Dst.size <= dst.Length);
		Array.Copy(src, cp.Orig.offI, dst, cp.Dst.offI, cp.Orig.size);
	}
	*/


	void ReorganizeArray(std::vector<T> &src, std::vector<CopyRegion> plan)
	{
		OPointer<std::vector<CopyRegion>> optPlan = OptimizePlan(plan);



		//create the list of copy conflicts
		std::set<CopyPlanSequenceDetail<T>*> backupList,seqPlan;
		for (auto cp : *optPlan) { seqPlan.insert(new CopyPlanSequenceDetail<T>(cp)); }


		for (auto cp1 : seqPlan)
		{
			for (auto cp2: seqPlan)
			{
				if (cp1 == cp2)
					continue;
				if ( cp2->Copy.Orig.IsAfter(cp1->Copy.Dst) )
				{
					break;
				}
				if (cp2->Copy.Orig.Intersects(cp1->Copy.Dst))
				{
					cp1->IsBlockedBy.insert(cp2);
					cp2->Blocks.insert(cp1);
				}
			}
		}



		while (seqPlan.size() > 0)
		{
			auto minElemIt = (std::min_element(seqPlan.begin(), seqPlan.end(), [](const CopyPlanSequenceDetail<T>* a, const CopyPlanSequenceDetail<T>* b) -> bool {return a->IsBlockedBy.size() < b->IsBlockedBy.size(); }));
			auto minElem = *minElemIt;

			if (minElem->IsBlockedBy.size() != 0)
			{
				for (auto it=minElem->IsBlockedBy.begin();it!=minElem->IsBlockedBy.end();it++)
				{
					auto blockingElem = *it;
					blockingElem->CreateBackup(src);
					blockingElem->RemoveBlocks();

					//Move the backed up element to the backed up elements list
					seqPlan.erase(blockingElem);
					backupList.insert(blockingElem);
				}
			}
			minElem->Copy.Execute(src);
			minElem->RemoveBlocks();
			seqPlan.erase(minElem);
			delete minElem;
		}
		for (auto backupElem : backupList)
		{
			backupElem->ApplyBackup(src);
			delete backupElem;
		}
	}
};
