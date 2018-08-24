#include "../catch.hpp"
#include <MGLEngine.Vulkan/Window/MWindow.h>
#include <MGLEngine.Vulkan/MemoryManager/VulkanBuffer.h>
#include "MGLEngine.Vulkan/VulkanContext/VulkanContext.h"
#include <MGLEngine.Shared/Topologies/Triangle2D.h>
#include "MGLEngine.Shared/Renders/CyclicColor.h"

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

TEST_CASE("Print Triangle")
{
	MGL::Window&  window = *GetWindow();
	ITopology2D *top = new Triangle2D(
		glm::vec2(0, 0),
		glm::vec2(0, 1),
		glm::vec2(1, 0)
	);
	IRender<Color2D> *render = new CyclicColor<Color2D>(
		{glm::vec3(1,1,1),glm::vec3(1,0,1),glm::vec3(0,0,1)}
	);


	window.GetVulkanContext()->GetShaderColor2D()->Add(top, render);

	window.EasyRun();

	return;

}



TEST_CASE("Vulkan Buffers Tests")
{
	MGL::Window&  window = *GetWindow();

	SECTION("a windows staging buffer allocation should have  correct size capacity")
	{
		VulkanMappedAutoSyncBuffer<double> vb(window.GetVulkanContext()->GetMemoryManager(), 20, 30,{VK_BUFFER_USAGE_VERTEX_BUFFER_BIT});
		REQUIRE(vb.size() == 20);
		REQUIRE(vb.capacity() >= 30);
		REQUIRE(vb.capacity()*sizeof(double) % vb.GetAlignment() == 0);
		
		VulkanMappedAutoSyncBuffer<double> vb2(window.GetVulkanContext()->GetMemoryManager(), 750, 2470, { VK_BUFFER_USAGE_VERTEX_BUFFER_BIT });
		REQUIRE(vb2.size() == 750);
		REQUIRE(vb2.capacity() >= 2470);
		REQUIRE(vb2.capacity()*sizeof(double) % vb2.GetAlignment() == 0);
	}

	SECTION("a staging buffer should allow read and write")
	{
		VulkanMappedAutoSyncBuffer<double> vb(window.GetVulkanContext()->GetMemoryManager(), 20, 30, { VK_BUFFER_USAGE_VERTEX_BUFFER_BIT });
		vb[0] = 1.0;
		vb[5] = 2.0;
		vb[19] = 3.0;
		
		REQUIRE(vb[0] == 1.0);
		REQUIRE(vb[5] == 2.0);
		REQUIRE(vb[19] == 3.0);
	}




}
