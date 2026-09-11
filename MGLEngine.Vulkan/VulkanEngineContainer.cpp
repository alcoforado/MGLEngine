#include "VulkanEngineContainer.h"
#include "VulkanEngine.h"

IGraphicLibrary* VulkanEngineContainer::GetLibrary(WindowOptions& wOp, AppConfiguration& appOp)
{
	return new MGL::VulkanEngine(wOp,appOp);
}
