#include <functional>
#include <memory>
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>
#include <MGLEngine.Shared/Interfaces/IAppBuilder.h>
 namespace MGL {
	class VulkanAppBuilder: public IAppBuilder  {
		private:
			std::shared_ptr<IMGLEngine> _pEngine;
			//configuraion options
			WindowOptions _windowOptions;
			AppConfiguration _vulkanConfiguration;

		
		public:
			virtual void WindowConfig(const std::function<void(IWindowOptions&)>& config)
			{
				config(_windowOptions);
			}

			virtual void AppConfig(const std::function<void(IAppConfiguration&)>& config)
			{
				config(_vulkanConfiguration);
			}

			

			virtual IMGLEngine& Init();
			
			
	};
}