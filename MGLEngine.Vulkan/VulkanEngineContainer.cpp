#include "VulkanEngineContainer.h"
#include "VulkanGL.h"

IGraphicLibrary* VulkanEngineContainer::GetLibrary(s_ptr<Window> window, AppConfiguration& appOp)
{
	return new MGL::VulkanGL(window,appOp);
}
