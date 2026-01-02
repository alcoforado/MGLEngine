#include "IndicesMemoryStream.h"
#include <MGLEngine.Shared/Utils/eassert.h>
IndicesMemoryStream::IndicesMemoryStream(uint32_t* indices, size_t size, size_t offDisplacement)
	:_indices(indices)
	, _max_size(size)
	, _offDisplacement(offDisplacement)
{
	_currentCount = 0;
}


IndicesMemoryStream& IndicesMemoryStream::operator<<(const std::vector<uint32_t>& v)
{
	eassert(v.size() + _currentCount <= _max_size, "Memory Stream overflow detected");
	for (size_t i = 0; i < v.size(); i++)
	{
		_indices[i] = v[i] + (uint32_t) _offDisplacement;
	}
	_currentCount += v.size();
	return *this;
}