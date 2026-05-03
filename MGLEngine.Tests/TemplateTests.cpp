#include "catch.hpp"
#include <type_traits>
#include <glm/glm.hpp>

struct A
{
	int X;
};

struct B
{
	double X;
};

template<class T>
class Test
{
public:
	
	template<typename T_=T>
	typename std::enable_if<std::is_same<int,decltype(T_::X)>::value,int>::type method1()
	{
		return 1;
	}
	
	template<typename T_ = T>
	typename std::enable_if<std::is_same<double, decltype(T_::X)>::value, int>::type method1()
	{
		return 2;
	}
};


TEST_CASE("Template selection")
{
	

	SECTION("Detect Equal types")
	{
		bool b = true;
		b=std::is_same<int, int32_t>::value;
		REQUIRE(b);

		b = std::is_same<double, int32_t>::value;
		REQUIRE(!b);

		b=std::is_same<int, decltype(A::X)>::value;
		REQUIRE(b);

		Test<A> ta;
		REQUIRE(ta.method1()==1);

		Test<B> tb;
		REQUIRE(tb.method1() == 2);

	}


}