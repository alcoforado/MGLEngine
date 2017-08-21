#include "../catch.hpp"
#include <MGLEngine.Vulkan/Window/MWindow.h>
#include "MGLEngine.Vulkan/RenderPipeline/VulkanStagingBuffer.h"
#include "MGLEngine.Vulkan/MGLContainer.h"
#include "MGLEngine.Vulkan/VulkanContext/VulkanContext.h"

TEST_CASE("Vulkan Windows Tests")
{

	SECTION("Create a window should not cause vulkan errorswork")
	{
		MGL::Window window;
		REQUIRE(!VulkanInstance::HasErrors());
	}
	
	SECTION("Close  a window should not cause vulkan errors")
	{
		{
			MGL::Window window;
		}
		REQUIRE(!VulkanInstance::HasErrors());
	}
}

TEST_CASE("Vulkan Buffers Tests")
{
	MGL::Window window;

	SECTION("a windows staging buffer allocation should have  correct size capacity")
	{
		VulkanStagingBuffer<double> vb(window.GetVulkanContext()->GetMemoryManager(), 20, 30);
		REQUIRE(vb.size() == 20);
		REQUIRE(vb.capacity() == 30);
	}



}
