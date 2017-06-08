#pragma once

#include "../Arrays/Indices.h"

class ArrayRegion
{
public:
	Index offI;
	Index size;
public:
	ArrayRegion(){}
	~ArrayRegion(){}
	ArrayRegion(int o,int s)
	{
		offI = o;
		size = s;
			
	}
	Index LastIndex() const
	{
		return offI + size - 1;
	}


	 bool ContinuouslyFollows(ArrayRegion dst) const
	 {
		return (offI == dst.offI + dst.size);
	}

	 bool Overlaps(ArrayRegion dst) const
	 {
		if (dst.offI > offI)
			return dst.offI - offI < size;
		else
			return offI - dst.offI < dst.size;
	}


	 bool IsAfter(ArrayRegion frag) const
	 {
		return frag.offI + frag.size < offI;
	}

	 bool Intersects(ArrayRegion frag) const
	 {
		return !(frag.offI + frag.size <= offI || frag.offI >= offI + size);
	}

};


