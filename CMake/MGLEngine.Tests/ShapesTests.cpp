#include "catch.hpp"
#include <MGLEngine.Shared/Topologies/Triangle2D.h>
#include "MGLEngine.Shared/Utils/JsonParser/mjson.h"


TEST_CASE("Triangle2D Serialization")
{
	
	SECTION("Triangle2D should serialize correctly")
	{
		Triangle2D t(glm::vec2(0, 0), glm::vec2(1, 1), glm::vec2(1, 3));

		auto str = t.Serialize();

		REQUIRE("{\"P0\":{\"x\":0.0,\"y\":0.0},\"P1\":{\"x\":1.0,\"y\":1.0},\"P2\":{\"x\":1.0,\"y\":3.0}}" == str);
	}

	SECTION("Triangle2D should deserialize correctly")
	{
		Triangle2D t(glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0));

		t.Deserialize("{\"P0\":{\"x\":0.0,\"y\":0.0},\"P1\":{\"x\":1.0,\"y\":1.0},\"P2\":{\"x\":1.0,\"y\":3.0}}");
		auto str = t.Serialize();

		REQUIRE(t.V1.x == 1.0);
		REQUIRE(t.V1.y == 1.0);
		REQUIRE(t.V2.x == 1.0);
		REQUIRE(t.V2.y == 3.0);
		REQUIRE("{\"P0\":{\"x\":0.0,\"y\":0.0},\"P1\":{\"x\":1.0,\"y\":1.0},\"P2\":{\"x\":1.0,\"y\":3.0}}" == str);
	}


}