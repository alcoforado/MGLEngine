#pragma once

#include "IArray.h"
#include <cstdint>
#include <vector>

typedef uint32_t Index;

class Indices : public IArray<uint32_t>
{
public:
	Indices(Index *p, size_t size);
	Indices(std::vector<uint32_t>& src);
	Indices(Index *p, size_t size, size_t capacity);
	
	~Indices();
	void AdjustArray(Index offO, Index offD);
	void AddOffset(Index off);
};

