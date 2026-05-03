#pragma once
#include <vector>

class ArrayFunctions
{
public:
	template<class T>
	static int FromBitFlagsToInt(const std::vector<T> v)
	{
		int r = 0;
		for(T e:v)
		{
			r |= e;
		}
		return r;
	}

};
