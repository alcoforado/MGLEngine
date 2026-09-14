#pragma once
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Interfaces/AppConfiguration.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
#include <MGLEngine.Shared//Utils/pointers.h>
class VulkanEngineContainer {

public:
	static IGraphicLibrary* GetLibrary(WindowOptions& wOp, AppConfiguration& appOp);

	
};