#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_COLOUR_WINDOWS
#include "catch.hpp"

int main(int argc, char* argv[])
{
	//global setup...
	int result = Catch::Session().run(argc, argv);

	//global clean-up...
	//getchar();
	return result;
}
