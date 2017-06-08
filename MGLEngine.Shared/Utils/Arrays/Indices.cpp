#include "Indices.h"


Indices::Indices(uint32_t *p, size_t size)
	:IArray<uint32_t>(p, size) {}

Indices::Indices(uint32_t *p, size_t size,size_t capacity)
	: IArray<uint32_t>(p, size,capacity) {}

Indices::Indices(std::vector<uint32_t>& src)
	:IArray<uint32_t>(src) {}


Indices::~Indices()
{
}

void Indices::AdjustArray(Index offO, Index offD)
{
	for (size_t i = 0; i < _size; i++)
	{
		_ptr[i] -= offO;
		_ptr[i] += offD;
	}
}

void Indices::AddOffset(Index off)
{
	for (size_t i = 0; i < _size; i++)
	{
		_ptr[i] += off;
	}
}
