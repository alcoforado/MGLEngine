#pragma once
#include <functional>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Interfaces/IAppConfiguration.h>

class IApp {
public:
	virtual void WindowConfig(const std::function<void(IWindowOptions&)>& config) = 0;
	virtual void AppConfig(const std::function<void(IAppConfiguration&)>& config) = 0;
	virtual void Init()=0;
};