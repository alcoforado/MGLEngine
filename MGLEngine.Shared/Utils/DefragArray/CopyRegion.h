#pragma once
#include "ArrayRegion.h"
#include <vector>
#include <cassert>
#include "../Arrays/IArray.h"
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
	void Execute(IArray<T> &src)
	{
		assert(Orig.LastIndex() < src.size());
		assert(Dst.LastIndex() < src.size());
		assert(Dst.size == Orig.size);
		auto p = src.data();
		memmove(src.data() + Dst.offI, src.data() + Orig.offI, Dst.size*sizeof(T));
	}
	
	template<class T>
	void Execute(IArray<T>&src, IArray<T> &dst)
	{
		//Assert non overlapping
		assert(!src.overlaps(dst));
		assert(Orig.LastIndex() < src.size());
		assert(Dst.LastIndex() < dst.size());
		assert(Dst.size == Orig.size);
		auto p = src.data();
		memcpy(dst.data() + Dst.offI, src.data() + Orig.offI, Dst.size * sizeof(T));
	}

};
