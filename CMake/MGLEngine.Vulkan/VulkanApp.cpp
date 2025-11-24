	#include "VulkanApp.h"
#include<algorithm>
using namespace MGL;
MGL::VulkanApp::~VulkanApp() {
	// Destructor implementation (if needed)
}


MGL::VulkanApp::VulkanApp() {
	//default values for options
	_windowOptions.Width = 800;
	_windowOptions.Height = 60;
	_windowOptions.FullScreen= false;
	_windowOptions.Title = "Vulkan Application";
	_pWindow = nullptr;
	_pVulkanInstance = nullptr;
}

void MGL::VulkanApp::Init() {
		_pWindow = new Window(_windowOptions);
		_pVulkanInstance = new VulkanInstance(
			_vulkanConfiguration.Name, 
			_vulkanConfiguration.EnableDebug);
		ChoosePhysicalDevice();
		CreateVulkanSurface();
		CreateGraphicsQueue();
		
}

void MGL::VulkanApp::CreateVulkanSurface() {
	_pVulkanSurface = new VulkanSurface(*_pPhysicalDevice, *_pWindow);
}

void MGL::VulkanApp::CreateGraphicsQueue() {
	auto& queues = _pPhysicalDevice->GetQueueFamilies();
	for (auto i = 0; i < queues.size();i++)
	{
		if (queues[i].IsGraphic && queues[i]
		{
			_pVulkanSurface->IsQueueCompatible(i);
		}
	}
	_pVulkanSurface = new VulkanSurface(*_pPhysicalDevice, *_pWindow);

}



int deviceScore(const VulkanPhysicalDevice& device) {
	int score = 0;
	// Example criteria for scoring
	if (device.IsDiscrete()) {
		score += 5000; // Prefer discrete GPUs
	}
	if (device.IsIntegrated())
	{
		score += 4000;
	}
	if (device.IsCPU()) {
		score += 3000; // Least preferred
	}
	if (device.IsVirtual()) {
		score = +2000;
	}
	if (device.HasComputeQueue()) {
		score += 500;
	}
	
	
	return score;
}

void MGL::VulkanApp::ChoosePhysicalDevice()
{
	auto &v=_pVulkanInstance->GetPhysicalDevices();
	std::vector<int> suitableDevices;
	for (int i = 0; i < v.size(); i++) {
		suitableDevices.push_back(i);

	}
	std::sort(suitableDevices.begin(),suitableDevices.end(),[v](int a, int b) {
		int scoreA = deviceScore(v[a]);
	    int scoreB=deviceScore(v[b]);
		if (scoreA == scoreB)
		{
			return v[a].GetProperties().limits.maxImageDimension1D > v[b].GetProperties().limits.maxImageDimension1D;
		}
		return scoreA > scoreB;
	});
	_pPhysicalDevice =  &(v[suitableDevices[0]]);
}
