#pragma once
#include "CopyRegion.h"
#include <list>
#include <vector>
#include <cassert>
#include <set>
#include "../Exception.h"
template<class T>
class CopyPlanSequenceDetail
{
public:
	CopyRegion Copy;
	std::list<CopyRegion> BlockCopyPlan;
	std::set<CopyPlanSequenceDetail<T>*> Blocks;
	std::set<CopyPlanSequenceDetail<T>*> IsBlockedBy;
	std::vector<T> Backup;

public:
	CopyPlanSequenceDetail(CopyRegion copy)
	{
		Copy = copy;
	}

	void ApplyBackup(std::vector<T>& defragArray)
	{
		assert(Backup.size() != 0);
		assert(Copy.Dst.offI + Copy.Dst.size <= defragArray.size());
		memcpy(defragArray.data()+Copy.Dst.offI, Backup.data(),Backup.size() * sizeof(T));
	}
	void CreateBackup(std::vector<T>&  defragArray)
	{
		Backup.resize(Copy.Orig.size);
		memcpy(Backup.data(), defragArray.data() + Copy.Orig.offI, sizeof(T)*Backup.size());
	}
	void RemoveBlocks()
	{
		for(CopyPlanSequenceDetail<T>* copyPlan : Blocks)
		{
			std::size_t found = copyPlan->IsBlockedBy.erase(this);
			if (!found)
				throw new Exception("Consistency Error found in blocks construction");
		}
	}
	~CopyPlanSequenceDetail(){}
};

