#include <cassert>
#ifndef VERTICEARRAY_H
#define VERTICEARRAY_H


#include <vector>
#include "IArray.h"
template<class MemberType>
class ArraySelect
{
	void *_data;
	int _size;
	int _type_off;
	int _member_off;


public:

	template<class ClassType>
	ArraySelect(IArray<ClassType> &data, MemberType ClassType::*vertice)
	{
		static_assert(sizeof(ClassType) % 4 == 0, "Type can only have 4 bytes alignment");
		_data = &(data[0]);
		_size = data.size();
		_type_off = sizeof(ClassType);
		_member_off = static_cast<void*>(&data[0].*vertice) - static_cast<void*>(&(data[0]));
	}


	int size() { return _size; }

	MemberType& operator[](int i) {
		assert(i<_size);
		return *((MemberType*)(_data + (i*_type_off + _member_off)));
	}

};



#endif // VERTICEARRAY_H
