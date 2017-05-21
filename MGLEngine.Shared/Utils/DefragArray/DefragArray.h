#pragma once
#include "CopyRegion.h"
#include "../opointer.h"
#include <vector>
#include <list>
#include "CopyPlanSequenceDetail.h"

template<class T>
class DefragArray
{
private:
	std::vector<CopyRegion>* OptimizePlan(std::vector<CopyRegion> p)
	{
		
		std::sort(p.first(), p.end(), [](const T&a, const T&b)->bool
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
					optimumPlan->Add(rg);
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
		auto backupList = new std::list<CopyPlanSequenceDetail<T>*>();
		var seqPlan = optPlan.Select(x = > new CopyPlanSequenceDetail<T>(x)).ToList();
		for (int i = 0; i<seqPlan.Count; i++)
		{
			var cp1 = seqPlan[i];
			for (int j = 0; j < seqPlan.Count && j != i; j++)
			{
				var cp2 = seqPlan[j];
				if (cp2.Copy.Orig.IsAfter(cp1.Copy.Dst))
				{
					break;
				}
				if (cp2.Copy.Orig.Intersects(cp1.Copy.Dst))
				{
					cp1.IsBlockedBy.Add(cp2);
					cp2.Blocks.Add(cp1);
				}
			}
		}



		while (seqPlan.Count > 0)
		{
			int minBlockedValue = int.MaxValue;
			int minBlockIndex = 0;
			int cI = 0;
			foreach(var p in seqPlan)
			{
				if (p.IsBlockedBy.Count < minBlockedValue)
				{
					minBlockedValue = p.IsBlockedBy.Count;
					minBlockIndex = cI;
				}
				cI++;
			}
			var minElem = seqPlan[minBlockIndex];
			if (minElem.IsBlockedBy.Count == 0)
				CopyArraySegment(src, src, minElem.Copy);
			else
			{
				foreach(var blockingElem in minElem.IsBlockedBy)
				{
					blockingElem.CreateBackup(src);
					blockingElem.RemoveBlocks();

					//Move the backed up element to the backed up elements list
					seqPlan.Remove(blockingElem);
					backupList.Add(blockingElem);
				}
			}

			minElem.RemoveBlocks();
			seqPlan.Remove(minElem);

		}
		foreach(var backupElem in backupList)
		{
			backupElem.ApplyBackup(src);
		}


	}


};
