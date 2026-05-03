#include "catch.hpp"
#include <MglEngine.HttpServer\HttpServer.h>
#include <MglEngine.HttpServer\Url.h>
TEST_CASE("URL Class")
{

	SECTION("Url Relative Path should decompose the path correctly removing trailing /")
	{
		Url url("/path1/path2/");
		REQUIRE(url.relativePath() == "path1/path2");
	};

	SECTION("Url Relative Path should decompose the path correctly removing repeated //")
	{
		Url url("//path1//path2//");
		REQUIRE(url.relativePath() == "path1/path2");
	};

	SECTION("Url with one query parameter should have that parameter in the query")
	{
		Url url("/path1/path2?param1=value1");
		REQUIRE((url.getQuery()).at("param1")=="value1");
	};

	SECTION("Url with 2 query parameter should have both parameters in the query")
	{
		Url url("/path1/path2?param1=value1&param2=value2");
		REQUIRE((url.getQuery()).at("param1") == "value1");
		REQUIRE((url.getQuery()).at("param2") == "value2");

	};


}

TEST_CASE("Router") {

	Router::ControllerCall f1 = [](WebApiContext& context) {
		return context.HttpOk("Ola1");
	};
	Router::ControllerCall f2 = [](WebApiContext& context) {
		return context.HttpOk("Ola2");
	};

	Router::ControllerCall f3 = [](WebApiContext& context) {
		return context.HttpOk("Ola3");
	};

	SECTION("No Matching routes return null")
	{
		Router r;
		r.Map(http::verb::get, "url1", f1);
		r.Map(http::verb::get, "url2/url3", f1);

		auto rm1 = r.MatchRoute(Url("url4"), "GET");
		auto rm2 = r.MatchRoute(Url("url2"), "GET");
		
		REQUIRE(!rm1);
		REQUIRE(!r.MatchRoute(Url("url1"),"POST"));


	}


	SECTION("Router should match based on specialization")
	{
		Router r;
		r.Map(http::verb::get, "url1", f1);
		r.Map(http::verb::get, "url2/url3", f2);
		r.Map(http::verb::get, "url4/url5/url6", f3);

		auto rm1 = r.MatchRoute(Url("url1"), "GET");
		auto rm2 = r.MatchRoute(Url("url2/url3"), "GET");
		auto rm3 = r.MatchRoute(Url("url4/url5/url6"), "GET");
		


		REQUIRE(rm1);
		REQUIRE(rm2);
		REQUIRE(rm3);
			
			

	}

	SECTION("Routers Parameters should be available")
	{
		Router r;
		r.Map(http::verb::get, "url1", f1);
		r.Map(http::verb::get, "url2/{url3}", f2);

		auto rm1 = r.MatchRoute(Url("url1"), "GET");
		auto rm2 = r.MatchRoute(Url("url2/match1"), "GET");

		REQUIRE(rm1->RouteParameters.size() == 0);
		REQUIRE(rm2->RouteParameters.size() == 1);
		REQUIRE(rm2->RouteParameters["url3"] == "match1");



	}




}