#include <functional>
#include <memory>
#include "Window/MWindow.h"
#include "VulkanContext/VulkanConfiguration.h"
#include "VulkanContext/VulkanInstance.h"
 namespace MGL {
	class VulkanApp {
		private:
			Window* _pWindow;
			VulkanInstance* _pVulkanInstance;

			WindowOptions _windowOptions;
			VulkanConfiguration _vulkanConfiguration;
		public:
			void WindowConfig(std::function<void(WindowOptions&)>& config)
			{
				config(_windowOptions);
			}

			void VulkanConfig(std::function<void(VulkanConfiguration&)>& config)
			{
				config(_vulkanConfiguration);
			}

			VulkanApp();
		
			~VulkanApp();
			void Init();
			
	};
}