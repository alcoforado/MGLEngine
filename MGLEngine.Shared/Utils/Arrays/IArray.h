#pragma once

#include <stddef.h>
#include <vector>
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
	
	explicit IArray(std::vector<OfType>& src)
	{
		_capacity = _size = src.size();
		_ptr = src.data();
	}


	IArray(OfType *p, size_t size,size_t capacity)
	{
		assert(size <= capacity);
		_ptr = p;
		_size = size;
		_capacity = capacity;
	}



	bool overlaps(IArray<OfType> &a)
	{
		return ((a._ptr + a._size - 1) < _ptr) || ((_ptr + _size - 1) < a._ptr);
	}

	void swap(IArray<OfType>& a)
	{
		IArray<OfType> aux = a;
		a = *this;
		*this = aux;
	}


	OfType& operator[](size_t i)
	{
		assert(i<_size);
		return _ptr[i];
	}
	size_t size() { return _size; }
	size_t capacity() { return _capacity; }
	OfType* GetPointer() { return _ptr; }

	void Resize(size_t size)
	{
		assert(size <= _capacity);
		_size = size;
	}

	OfType* data()
	{
		return _ptr;
	}

	void clear()
	{
		_size = 0;
		_ptr = nullptr;
	}
};

#endif // IARRAY_H