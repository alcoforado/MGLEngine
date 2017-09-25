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
#include "../Shaders/ShaderColor2D.h"
#include <Topologies/Triangle2D.h>
#include <Renders/CyclicColor.h>


VulkanContext::VulkanContext(GLFWwindow * window)
	:_vkLogicalDevice(_vkInstance.GetPhysicalDevices()[0].CreateLogicalDevice(window)),
	_commandPool(*_vkLogicalDevice),
	_memoryMngr(*_vkLogicalDevice,2*_MB)
{
	//Set Swap Chain
	_pSwapChain = new VulkanSwapChain(*_vkLogicalDevice);
	_render = new ShaderColor2D(*this);

	auto tria = new Triangle2D(
		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(0, 1)
	);


	std::vector<glm::vec3> colors;
	colors.push_back(glm::vec3(0, 1, 0));
	auto painter = new CyclicColor<ShaderColor2D::VerticeType>(colors);

	_render->Add(tria,painter);

	_drawContext.RenderContext = this;
}




void VulkanContext::OnResize(GLFWwindow *window, int newWidth,int newHeight)
{
	_vkLogicalDevice->WaitToBeIdle();
	_pSwapChain.if_free();
	_vkLogicalDevice->GetSurface().UpdateWindowDims(newWidth,newHeight);
	_pSwapChain = new VulkanSwapChain(*_vkLogicalDevice);
	_drawContext.WindowResized = true;
}


VulkanContext::~VulkanContext()
{
	delete _render;
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
	
	_drawContext.RenderContext = this;
	_drawContext.CurrentSemaphore = _pSwapChain->NextImagePipelineAsync(); 
	_drawContext.CurrentSemaphore = _render->Draw(&_drawContext);
	_pSwapChain->Present(*_drawContext.CurrentSemaphore);
	_drawContext.WindowResized = false;


}
