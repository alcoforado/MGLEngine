#include <functional>
#include <memory>
#include "Window/MWindow.h"
#include "VulkanContext/VulkanConfiguration.h"
#include "VulkanContext/VulkanInstance.h"
#include "VulkanContext/VulkanPhysicalDevice.h"

 namespace MGL {
	class VulkanApp {
		private:
			Window* _pWindow=nullptr;
			VulkanInstance* _pVulkanInstance=nullptr;
			const VulkanPhysicalDevice* _pPhysicalDevice = nullptr; //Active physical device
			
			WindowOptions _windowOptions;
			VulkanConfiguration _vulkanConfiguration;



		private:
			void ChoosePhysicalDevice();
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