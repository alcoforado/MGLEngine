#include "../catch.hpp"
#include <MGLEngine.Vulkan/Window/MWindow.h>
#include "MGLEngine.Vulkan/RenderPipeline/VulkanStagingBuffer.h"
#include "MGLEngine.Vulkan/MGLContainerVulkan.h"
#include "MGLEngine.Vulkan/VulkanContext/VulkanContext.h"

MGL::Window *pWindow = nullptr;

MGL::Window* GetWindow()
{
	if (!pWindow)
		pWindow = new MGL::Window();
	return pWindow;
}

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
	MGL::Window&  window = *GetWindow();

	SECTION("a windows staging buffer allocation should have  correct size capacity")
	{
		VulkanStagingBuffer<double> vb(window.GetVulkanContext()->GetMemoryManager(), 20, 30);
		REQUIRE(vb.size() == 20);
		REQUIRE(vb.capacity() > 30);
		REQUIRE(vb.capacity()*sizeof(double) % vb.GetAlignment() == 0);
		
		VulkanStagingBuffer<double> vb2(window.GetVulkanContext()->GetMemoryManager(), 750, 2470);
		REQUIRE(vb2.size() == 750);
		REQUIRE(vb2.capacity() > 2470);
		REQUIRE(vb2.capacity()*sizeof(double) % vb2.GetAlignment() == 0);
	}

	SECTION("a staging buffer should allow read and write")
	{
		VulkanStagingBuffer<double> vb(window.GetVulkanContext()->GetMemoryManager(), 20, 30);
		vb[0] = 1.0;
		vb[5] = 2.0;
		vb[19] = 3.0;
		
		REQUIRE(vb[0] == 1.0);
		REQUIRE(vb[5] == 2.0);
		REQUIRE(vb[19] == 3.0);
	}




}
