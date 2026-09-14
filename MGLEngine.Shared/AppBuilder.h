
#include <MGLEngine.Shared/MGLEngine.h>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Interfaces/AppConfiguration.h>
#include <MGLEngine.Shared/Utils/pointers.h>

class AppBuilder {
private:
	s_ptr<MGLEngine> _pEngine;
	//configuraion options
	WindowOptions _windowOptions;
	AppConfiguration _appConfiguration;


		public:
			virtual void WindowConfig(const std::function<void(IWindowOptions&)>& config)
			{
				config(_windowOptions);
			}

			virtual void AppConfig(const std::function<void(AppConfiguration&)>& config)
			{
				config(_appConfiguration);
			}



			virtual MGLEngine& Init();


	};
