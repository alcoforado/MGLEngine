#include "catch.hpp"
#include "MGLEngine.Shared/Utils/JsonParser/JsonParser.h"
#include <glm/vec3.hpp>

TEST_CASE("MJsonParser Serialization")
{

	SECTION("Vec2 should serialize deserialize correctly")
	{
		glm::vec2 v(1, 2);
		JsonParser j;

		j["V"] = v;

		glm::vec2 r = j["V"];
		auto rstr = j.dump();
		REQUIRE(j.dump() == "{\"V\":{\"x\":1.0,\"y\":2.0}}");
		REQUIRE(r.x == v.x);
		REQUIRE(r.y == v.y);
		
		
		
	}


	SECTION("Vec3 should serialize deserialize correctly")
	{
		glm::vec3 v(1, 2,3);
		JsonParser j;

		j["V"] = v;

		glm::vec3 r = j["V"];
		auto rstr = j.dump();
		REQUIRE(j.dump() == "{\"V\":{\"x\":1.0,\"y\":2.0,\"z\":3.0}}");
		REQUIRE(r.x == v.x);
		REQUIRE(r.y == v.y);
		REQUIRE(r.z == v.z);



	}

	SECTION("Color should serialize deserialize correctly")
	{
		glm::vec3 v(1, 2, 3);
		JsonParser j;

		
		j["V"]=JsonParser::SerializeAsColor(v);



		glm::vec3 r = j["V"];
		auto rstr = j.dump();
		REQUIRE(j.dump() == "{\"V\":{\"b\":3.0,\"g\":2.0,\"r\":1.0}}");
		REQUIRE(r.x == v.x);
		REQUIRE(r.y == v.y);
		REQUIRE(r.z == v.z);



	}



}