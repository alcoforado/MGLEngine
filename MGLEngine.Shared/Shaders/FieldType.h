#pragma once
#include<stddef.h>


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
		inline static  bool _isFloatBased[] = {
			false, // TYPE_UINT
			true,    // TYPE_FLOAT
			true,  // TYPE_VEC_FLOAT_2
			true,  // TYPE_VEC_FLOAT_3
			true   // TYPE_VEC_FLOAT_4
		};
		constexpr   static  unsigned _fieldsPerElement[] = {
			1, // TYPE_UINT
			1,  // TYPE_FLOAT
			2,  // TYPE_VEC_FLOAT_2
			3,  // TYPE_VEC_FLOAT_3
			4   // TYPE_VEC_FLOAT_4
		};
		constexpr   static  unsigned _sizeOf[] = { //total size in bytes
			4, // TYPE_UINT
			4,  // TYPE_FLOAT
			8,  // TYPE_VEC_FLOAT_2,
			12, //  TYPE_VEC_FLOAT_3,
			16,   // TYPE_VEC_FLOAT_4
		};
		
	public:
		static unsigned int sizeOfType(FieldType type) {
			return _sizeOf[type];
		}
		


};