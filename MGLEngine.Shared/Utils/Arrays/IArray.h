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
	size_t _capacity;
public:
	IArray(OfType *p,size_t size)
	{
		_ptr = p;
		_size = size;
		_capacity = size;
	}

	IArray(OfType *p, size_t size,size_t capacity)
	{
		assert(size <= capacity);
		_ptr = p;
		_size = size;
		_capacity = capacity;
	}




	OfType& operator[](size_t i)
	{
		assert(i<_size);
		return _ptr[i];
	}
	size_t size() { return _size; }

	OfType* GetPointer() { return _ptr; }

	void Resize(size_t size)
	{
		assert(size <= capacity);
		_size = size;
	}
};

#endif // IARRAY_H