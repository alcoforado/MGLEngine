#pragma once
class ArrayRegion
{
public:
	int offI;
	int size;
public:
	ArrayRegion(){}
	~ArrayRegion(){}

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


