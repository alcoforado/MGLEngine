#pragma once



enum FieldType {
	TYPE_UINT = 0,
	TYPE_FLOAT = 1,
	TYPE_VEC_FLOAT_2 = 2,
	TYPE_VEC_FLOAT_4 = 3
	// Add other types as needed
};

class FieldTypeInfo2 {

public:
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
	

};