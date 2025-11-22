	#include "VulkanApp.h"

MGL::VulkanApp::~VulkanApp() {
	// Destructor implementation (if needed)
}
MGL::VulkanApp::VulkanApp() {
	//default values for options
	_windowOptions.Width = 800;
	_windowOptions.Height = 60;
	_windowOptions.FullScreen= false;
	_windowOptions.Title = "Vulkan Application";
}

void MGL::VulkanApp::Init() {
		_pWindow = new Window(_windowOptions);
		_pVulkanInstance = new VulkanInstance(
			_vulkanConfiguration.Name, 
			_vulkanConfiguration.EnableDebug);

		
}


