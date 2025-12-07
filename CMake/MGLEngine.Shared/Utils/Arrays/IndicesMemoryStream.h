#pragma once
#include<cstdint>
#include <vector>
class IndicesMemoryStream {

	uint32_t* _indices;
	size_t _max_size;
	uint32_t _offDisplacement;
	uint32_t _currentCount;
public:
	IndicesMemoryStream(uint32_t* indices, size_t size, uint32_t offDisplacement);



	IndicesMemoryStream& operator<<(const std::vector<uint32_t>& index);
};