#pragma once
#include <functional>
#include <memory>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Interfaces/IAppConfiguration.h>
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>
class IAppBuilder {
public:
	virtual void WindowConfig(const std::function<void(IWindowOptions&)>& config) = 0;
	virtual void AppConfig(const std::function<void(IAppConfiguration&)>& config) = 0;
	virtual IMGLEngine& Init()=0;
};