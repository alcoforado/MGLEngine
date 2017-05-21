#include "VulkanContext.h"
#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>
#include <Utils/Exception.h>
#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <fstream>
#include "../VulkanUtils.h"
#include "../Renders/RenderColor2D.h"


VulkanContext::VulkanContext(GLFWwindow * window)
	:_vkLogicalDevice(_vkInstance.GetPhysicalDevices()[0].CreateLogicalDevice(window)),
	_commandPool(_vkLogicalDevice)

{
	//Set Swap Chain
	_pSwapChain = new VulkanSwapChain(_vkLogicalDevice.GetSurface(), _vkLogicalDevice);
	render = new RenderColor2D(*this);


	
}


void VulkanContext::OnResize(GLFWwindow *window )
{
	delete render;
	_pSwapChain.if_free();
	_vkLogicalDevice.OnResizeWindow(window);

	_pSwapChain = new VulkanSwapChain(_vkLogicalDevice.GetSurface(), _vkLogicalDevice);
	render = new RenderColor2D(*this);
}


VulkanContext::~VulkanContext()
{
	delete render;
	_pSwapChain.if_free();
}





void VulkanContext::Initialize(GLFWwindow * window)
{
}

std::vector<VulkanPhysicalDevice> VulkanContext::GetPhysicalDevices(VkInstance& inst) const
{
	return _vkInstance.GetPhysicalDevices();
}


void VulkanContext::Draw()
{
	auto &s1 = _pSwapChain->NextImagePipelineAsync();
	auto &s2 = render->Draw(s1);
	_pSwapChain->Present(s2);
	


}
