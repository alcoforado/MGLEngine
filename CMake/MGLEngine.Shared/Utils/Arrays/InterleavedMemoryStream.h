#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

enum ElementType {
	TYPE_UINT=0,
	TYPE_FLOAT=1,
	TYPE_VEC_FLOAT_2=2,
	TYPE_VEC_FLOAT_4=3
	// Add other types as needed
};
class InterleavedMemoryStream {
	
	uint8_t* _pData; // Pointer to the first element in the array of interleaved elements
	size_t _elementSize; // Size of each element in bytes
	size_t _stride; // Stride between elements in bytes
	size_t _maxElementCount; // Total number of elements the memory stream can hold
	ElementType _elemType; // Type of elements stored in the stream
	size_t _currentOffBytes; // Current offset in bytes
	size_t _currentElementCount; // Current number of elements written
	inline static  unsigned elementSizeTable[] = {
		sizeof(unsigned), // TYPE_UINT
		sizeof(float),    // TYPE_FLOAT
		sizeof(float)*2,  // TYPE_VEC_FLOAT_2
		sizeof(float)*4   // TYPE_VEC_FLOAT_4
	};
	inline static  bool _isFloatBased[] = {
		false, // TYPE_UINT
		true,    // TYPE_FLOAT
		true,  // TYPE_VEC_FLOAT_2
		true   // TYPE_VEC_FLOAT_4
	};
	constexpr   static  unsigned _fieldsPerElement[] = {
		1, // TYPE_UINT
		1,  // TYPE_FLOAT
		2,  // TYPE_VEC_FLOAT_2
		4   // TYPE_VEC_FLOAT_4
	};
	InterleavedMemoryStream& operator<<(const std::vector<uint32_t>& v);



public:
	InterleavedMemoryStream(uint8_t* pData, size_t stride, size_t maxNumElements, enum ElementType elemType);
	
	InterleavedMemoryStream& operator<<(float value);
	InterleavedMemoryStream& operator<<(const glm::vec2 &v);
	InterleavedMemoryStream& operator<<(const glm::vec4 &v);
	InterleavedMemoryStream& operator<<(const std::vector<float>&v);
	~InterleavedMemoryStream() {}
	
};