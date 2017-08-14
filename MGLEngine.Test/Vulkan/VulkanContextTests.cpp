#include "../catch.hpp"
#include <MGLEngine.Vulkan/Window/MWindow.h>

TEST_CASE("Vulkan Windows Tests")
{

		SECTION("Create a window should not cause vulkan errorswork")
		{
			MGL::Window window;
			REQUIRE(!VulkanInstance::HasErrors());
		}
	
		SECTION("Close  a window should not cause vulkan errorswork")
		{
			{
				MGL::Window window;
			}
			REQUIRE(!VulkanInstance::HasErrors());
		}


}