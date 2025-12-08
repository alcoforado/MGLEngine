#include <MGLEngine.Shared/MGLContainer.h>
#include <MGLEngine.Vulkan/VulkanApp.h>

std::shared_ptr<IApp> MGLContainer::GetApp()
{
	return std::make_shared<MGL::VulkanApp>();
}