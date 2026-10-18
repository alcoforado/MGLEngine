#include "VulkanEngineContainer.h"
#include "VulkanGL.h"

IGraphicLibrary* VulkanEngineContainer::GetLibrary(s_ptr<MWindow> window, AppConfiguration& appOp)
{
	return new MGL::VulkanGL(window,appOp);
}
