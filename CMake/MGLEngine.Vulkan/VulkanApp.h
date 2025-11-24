#include <functional>
#include <memory>
#include "Window/MWindow.h"
#include "VulkanContext/VulkanConfiguration.h"
#include "VulkanContext/VulkanInstance.h"
#include "VulkanContext/VulkanPhysicalDevice.h"
#include "VulkanContext/VulkanSurface.h"

#include <unordered_map>
#include "ShaderContext.h"
 namespace MGL {
	class VulkanApp {
		private:
			Window* _pWindow=nullptr;
			VulkanInstance* _pVulkanInstance=nullptr;
			const VulkanPhysicalDevice* _pPhysicalDevice = nullptr; //Active physical device
			VulkanSurface* _pVulkanSurface;
			WindowOptions _windowOptions;
			VulkanConfiguration _vulkanConfiguration;
			std::unordered_map<std::string, ShaderContext> _shaders;


		private:
			void ChoosePhysicalDevice();
			void CreateVulkanSurface();
			void CreateGraphicsQueue();
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