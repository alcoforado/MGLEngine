#pragma once
#include<cstdint>
#include <vector>
class IndicesMemoryStream {

	uint32_t* _indices;
	size_t _max_size;
	size_t _offDisplacement;
	size_t _currentCount;
public:
	IndicesMemoryStream(uint32_t* indices, size_t size, size_t offDisplacement);



	IndicesMemoryStream& operator<<(const std::vector<size_t>& index);

	IndicesMemoryStream& operator<<(size_t index);

	template<std::size_t N>
	IndicesMemoryStream& operator<<(const std::array<size_t, N>& v)
	{
		eassert(v.size() + _currentCount <= _max_size, "Memory Stream overflow detected");
		for (size_t i = 0; i < v.size(); i++)
		{
			_indices[_currentCount++] = v[i] + _offDisplacement;
		}
		return *this;
	}
};