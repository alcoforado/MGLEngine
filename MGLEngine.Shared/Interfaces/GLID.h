#pragma once

#include <vector>
#include <limits>

//Graphic Library ID
struct GLID {
	size_t index;
	size_t type;


	GLID() {
		type = index = std::numeric_limits<size_t>::max();
	}
	GLID(size_t type, size_t index)
	{
		this->index = index;
		this->type = type;
	}

	bool Undefined() const {
		return (type == index) && type == std::numeric_limits<size_t>::max();
	}
};