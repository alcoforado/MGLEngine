#include "catch.hpp"
#include <MGLEngine.Shared/Utils/Arrays/IArray.h>
#include "MGLEngine.Shared/Utils/Arrays/ArraySelect.h"

struct TStruct
{
	float d1;
	float d2;
	float d3;
};


TEST_CASE("IArray")
{
	int heap[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	TStruct *heapStruct = new TStruct[10];
	IArray<TStruct> array(heapStruct, 5);
	ArraySelect<float> v1(array, &TStruct::d1);
	ArraySelect<float> v2(array, &TStruct::d2);
	ArraySelect<float> v3(array, &TStruct::d3);

	SECTION("IArray should map correctly to its heap")
	{
		IArray<int> t(heap + 2, 5);

		REQUIRE(t.size() == 5);

		int j = 0;
		for (int i = 0; i < t.size(); i++)
		{
			t[i] = ++j;
		};

		REQUIRE(heap[2] == 1);
		REQUIRE(heap[3] == 2);
		REQUIRE(heap[4] == 3);
		REQUIRE(heap[5] == 4);
		REQUIRE(heap[6] == 5);
	}
	

	SECTION("IArraySelect should set the right member")
	{
		heapStruct[2].d1 = heapStruct[2].d3 = 0;
		heapStruct[4].d1 = heapStruct[4].d3 = 0;
		v2[2] = 9.0;
		v2[4] = 3.0;
		REQUIRE(heapStruct[2].d2 == 9);
		REQUIRE(heapStruct[4].d2 == 3);
	}



}
