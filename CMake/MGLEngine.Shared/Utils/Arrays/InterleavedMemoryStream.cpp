#pragma once
#include "InterleavedMemoryStream.h"
#include <MGLEngine.Shared/Utils/eassert.h>
#include "IndicesMemoryStream.h"
InterleavedMemoryStream::InterleavedMemoryStream(uint8_t* pData, size_t stride, size_t maxNumElements, enum FieldType elemType)
{
	_pData = pData;
	_elementSize = elementSizeTable[elemType];
	_stride = stride;
	_maxElementCount = maxNumElements;
	_elemType = elemType;
	_currentOffBytes = 0;
	_currentElementCount = 0;

}
InterleavedMemoryStream& InterleavedMemoryStream::operator<<(float value)
{
	eassert(_elemType == TYPE_FLOAT, "Incompatible Types");
	eassert(_currentElementCount < _maxElementCount, "MemoryStream overflow detected");
	float* fp = reinterpret_cast<float*>(_pData + _currentOffBytes);
	*fp = value;
	_currentElementCount++;
	_currentOffBytes += _stride;
	return *this;
}

InterleavedMemoryStream& InterleavedMemoryStream::operator<<(const glm::vec2 &v)
{
	eassert(_elemType == TYPE_VEC_FLOAT_2, "Incompatible Types");
	eassert(_currentElementCount < _maxElementCount, "MemoryStream overflow detected");
	float* fp = reinterpret_cast<float*>(_pData + _currentOffBytes);
	fp[0] = v.x;
	fp[1] = v.y;
	_currentElementCount++;
	_currentOffBytes += _stride;
	return *this;
}

InterleavedMemoryStream& InterleavedMemoryStream::operator<<(const glm::vec4 &v)
{
	eassert(_elemType == TYPE_VEC_FLOAT_2, "Incompatible Types");
	eassert(_currentElementCount < _maxElementCount, "MemoryStream overflow detected");
	float* fp = reinterpret_cast<float*>(_pData + _currentOffBytes);
	fp[0] = v.x;
	fp[1] = v.y;
	fp[2] = v.z;
	fp[3] = v.w;

	_currentElementCount++;
	_currentOffBytes += _stride;
	return *this;
}


InterleavedMemoryStream& InterleavedMemoryStream::operator<<(const std::vector<float>& v)
{
	const uint32_t floatsPerElement = _fieldsPerElement[_elemType];

	eassert(_isFloatBased[_elemType], "Incompatible Types");
	eassert((v.size() % floatsPerElement) == 0, "Vector passed has incompatible dimensions");
	eassert(_currentElementCount + (v.size()/floatsPerElement) <= _maxElementCount, "Vector passed is too big. It won't fit in array");


	float* fp = reinterpret_cast<float*>(_pData + _currentOffBytes);
	uint32_t fieldN = 0;
	for (size_t i = 0; i < v.size();)
	{
		for (size_t j = 0; j < floatsPerElement;)
		{
			fp[j++] = v[i++];
		}
			
		_currentElementCount++;
		_currentOffBytes += _stride;
		fp = reinterpret_cast<float*>(_pData + _currentOffBytes);
	}
	return *this;
	// TODO: insert return statement here

}





