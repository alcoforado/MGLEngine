#pragma once
#include<stddef.h>
#include <vector>

enum FieldType {
	TYPE_UINT = 0,
	TYPE_FLOAT = 1,
	TYPE_VEC_FLOAT_2 = 2,
	TYPE_VEC_FLOAT_3 = 3,
	TYPE_VEC_FLOAT_4 = 4
	// Add other types as needed
};

class FieldTypeInfo {

	private:
		inline static  std::vector<bool> _isFloatBased = {
			false, // TYPE_UINT
			true,    // TYPE_FLOAT
			true,  // TYPE_VEC_FLOAT_2
			true,  // TYPE_VEC_FLOAT_3
			true   // TYPE_VEC_FLOAT_4
		};
		inline static  std::vector<uint32_t> _fieldsPerElement = {
			1, // TYPE_UINT
			1,  // TYPE_FLOAT
			2,  // TYPE_VEC_FLOAT_2
			3,  // TYPE_VEC_FLOAT_3
			4   // TYPE_VEC_FLOAT_4
		};
		inline static  std::vector<uint32_t> _sizeOf = {
			sizeof(unsigned), // TYPE_UINT
			sizeof(float),    // TYPE_FLOAT
			sizeof(float) * 2,  // TYPE_VEC_FLOAT_2
			sizeof(float) * 3,  // TYPE_VEC_FLOAT_3
			sizeof(float) * 4   // TYPE_VEC_FLOAT_4
		};
	public:
		static unsigned int sizeOfType(FieldType type) {
			return _sizeOf[type];
		}
		
		static unsigned int fieldsPerElement(FieldType type)
		{
			return _fieldsPerElement[type];
		}

		static bool  isFloat(FieldType type)
		{
			return _isFloatBased[type];
		}


};