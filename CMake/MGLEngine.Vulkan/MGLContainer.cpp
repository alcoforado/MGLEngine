#include <MGLEngine.Shared/MGLContainer.h>
#include <MGLEngine.Vulkan/VulkanAppBuilder.h>

std::shared_ptr<IAppBuilder> MGLContainer::GetApp()
{

	return std::make_shared<MGL::VulkanAppBuilder>();
}