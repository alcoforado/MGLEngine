#include "catch.hpp"
#include <MGLEngine.Shared/Utils/Observable.h>


TEST_CASE("Observables")
{
	
	Observable<int> obs,obs2;
	int a = 1, b = 3;
	Listener<int> lst1([&a](int e) {a += e; });
	Listener<int> lst2([&b](int e) {b += e; });
	lst1.Listen(&obs);
	lst2.Listen(&obs);
	lst1.Listen(&obs2);
	lst2.Listen(&obs2);
	SECTION("Observables should execute all listeners")
	{
		int e = 3;
		obs.Emit(e);
		REQUIRE(a == 4);
		REQUIRE(b == 6);
	}
	
	SECTION("Multiple Observables should execute all listeners")
	{
		int e = 3;
		obs.Emit(e);
		REQUIRE(a == 4);
		REQUIRE(b == 6);
		obs2.Emit(e);
		REQUIRE(a == 7);
		REQUIRE(b == 9);
	
	}

	SECTION("Disposed Listener is never called again")
	{
		lst1.Dispose();
		int e = 3;
		obs.Emit(e);
		obs2.Emit(e);

		REQUIRE(a == 1);
		REQUIRE(b == 9);

	}

	SECTION("Detached Listener is never called again by that specific observer")
	{
		lst1.DetachFromObserver(&obs);
		int e = 3;
		obs.Emit(e);
		e = 4;
		obs2.Emit(e);

		REQUIRE(a == 5);
		REQUIRE(b == 10);

	}



	
}
