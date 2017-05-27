#pragma once

#include <stddef.h>
#ifndef IARRAY_H
#define IARRAY_H
#include<assert.h>
template <class OfType>
class IArray
{

protected:
	IArray() { _ptr = NULL; _size = 0; }
	OfType *_ptr;
	size_t _size;
public:
	IArray(OfType *p,size_t size)
	{
		_size = size;
	}


	OfType& operator[](Index i)
	{
		assert(i<_size);
		return _ptr[i];
	}
	size_t size() { return _size; }

	OfType* GetPointer() { return _ptr; }
};

#endif // IARRAY_H