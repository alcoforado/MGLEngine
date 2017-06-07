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
