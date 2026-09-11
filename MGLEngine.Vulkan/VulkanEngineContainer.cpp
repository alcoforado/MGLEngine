#include "VulkanEngineContainer.h"
#include "VulkanGL.h"

IGraphicLibrary* VulkanEngineContainer::GetLibrary(WindowOptions& wOp, AppConfiguration& appOp)
{
	return new MGL::VulkanGL(wOp,appOp);
}
