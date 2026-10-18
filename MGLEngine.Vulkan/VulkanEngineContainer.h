#pragma once
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Interfaces/AppConfiguration.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
#include <MGLEngine.Shared/Utils/pointers.h>

class MWindow;

class VulkanEngineContainer {

public:
	static IGraphicLibrary* GetLibrary(s_ptr<MWindow> window, AppConfiguration& appOp);

	
};