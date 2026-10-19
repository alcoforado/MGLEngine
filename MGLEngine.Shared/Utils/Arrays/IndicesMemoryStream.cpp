#include "IndicesMemoryStream.h"
#include <MGLEngine.Shared/Utils/eassert.h>
#include <array>
IndicesMemoryStream::IndicesMemoryStream(uint32_t* indices, size_t size, size_t offDisplacement)
	:_indices(indices)
	, _max_size(size)
	, _offDisplacement(offDisplacement)
{
	_currentCount = 0;
}


IndicesMemoryStream& IndicesMemoryStream::operator<<(const std::vector<size_t>& v)
{
	eassert(v.size() + _currentCount <= _max_size, "Memory Stream overflow detected");
	for (size_t i = 0; i < v.size(); i++)
	{
		_indices[_currentCount++] = v[i] +  _offDisplacement;
	}
	return *this;
}





IndicesMemoryStream& IndicesMemoryStream::operator<<(size_t index)
{
	eassert(1 + _currentCount <= _max_size, "Memory Stream overflow detected");
	_indices[++_currentCount] = index + _offDisplacement;
	return *this;
}
