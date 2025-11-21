module;
#include <functional>
#include <memory>
#include <MGLEngine.Vulkan/Window/MWindow.h>
export module VulkanApp;

export namespace MGL {
	class VulkanApp {
		private:
			std::unique_ptr<Window*> _pWindow;
			WindowOptions _windowOptions;
		public:
			void WindowConfig(std::function<void(WindowOptions&)>& config)
			{
				config(_windowOptions);
			}

			VulkanApp();
		
			~VulkanApp();
			void Init()
			{
				_pWindow = std::make_unique<Window*>(new Window(_windowOptions));
			}
	};
}