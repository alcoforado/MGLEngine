#pragma once

#include "IArray.h"
#include <cstdint>
#include <vector>
class Indices : public IArray<uint32_t>
{
public:
	Indices(uint32_t *p, size_t size);
	Indices(std::vector<uint32_t>& src);
	Indices(uint32_t *p, size_t size, size_t capacity);
	
	~Indices();
};

