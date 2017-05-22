#pragma once
#include "ArrayRegion.h"
#include <vector>
#include <cassert>
class CopyRegion
{
public:
	ArrayRegion Orig;
	ArrayRegion Dst;


	CopyRegion(){}

	CopyRegion(ArrayRegion orig,ArrayRegion dst)
	{
		Orig = orig;
		Dst = dst;
	}
	bool TryRightMerge( CopyRegion copyPlan)
	{
		if (copyPlan.Orig.ContinuouslyFollows(Orig) &&
			copyPlan.Dst.ContinuouslyFollows(Dst))
		{
			Orig.size += copyPlan.Orig.size;
			Dst.size += copyPlan.Dst.size;
			return true;
		}
		return false;
	}

	template<class T>
	void Execute(std::vector<T> &src)
	{
		assert(Orig.LastIndex() < src.size());
		assert(Dst.LastIndex() < src.size());
		assert(Dst.size == Orig.size);
		auto p = src.data();
		memcpy(src.data() + Dst.offI, src.data() + Orig.offI, Dst.size*sizeof(T));
	}

};
