#include "catch.hpp"
#include <type_traits>
struct A
{
	int X;
};


TEST_CASE("Template selection")
{
	

	SECTION("Detect Intersections")
	{
		bool b = true;
		b=std::is_same<int, int32_t>::value;
		REQUIRE(b);
	}


}