#pragma once
#include "ArrayRegion.h"

class CopyRegion
{
public:
	ArrayRegion Dst;
	ArrayRegion Orig;

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

};