
#include <catch.hpp>
#include "VulkanTestsHelper.h"
#include "MGLEngine.Vulkan/RenderPipeline/VulkanSemaphorePool.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanContext.h>


TEST_CASE("Sempahore Pool Tests")
{
	auto w = VulkanTestsHelper::GetWindow();
	auto pool = new VulkanSemaphorePool(w->GetVulkanContext()->GetLogicalDevice());
	
	auto h1 = pool->Allocate();
	auto h2 = pool->Allocate();
	auto h3 = pool->Allocate();

	SECTION("Successive allocations should give different semaphores")
	{
		REQUIRE(h1->GetResource()->GetHandle() != h2->GetResource()->GetHandle());
		REQUIRE(h1->GetResource()->GetHandle() != h3->GetResource()->GetHandle());
		REQUIRE(h2->GetResource()->GetHandle() != h3->GetResource()->GetHandle());
	}


}