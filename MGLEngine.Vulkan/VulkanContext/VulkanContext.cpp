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
void VulkanContext::OnWindowResized(GLFWwindow* window, int width, int height) {
	if (width == 0 || height == 0) return;

	VulkanContext *ctx = reinterpret_cast<VulkanContext*>(glfwGetWindowUserPointer(window));
	ctx->OnResize(window);
}


VulkanContext::VulkanContext(GLFWwindow * window)
	:_vkLogicalDevice(_vkInstance.GetPhysicalDevices()[0].CreateLogicalDevice(window)),
	_commandPool(_vkLogicalDevice),
	_memoryMngr(_vkLogicalDevice,2*_MB)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, OnWindowResized);
	//Set Swap Chain
	_pSwapChain = new VulkanSwapChain(_vkLogicalDevice.GetSurface(), _vkLogicalDevice);
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


}




void VulkanContext::OnResize(GLFWwindow *window)
{
	_vkLogicalDevice.WaitToBeIdle();

	delete _render;
	_pSwapChain.if_free();
	_vkLogicalDevice.OnResizeWindow(window);

	_pSwapChain = new VulkanSwapChain(_vkLogicalDevice.GetSurface(), _vkLogicalDevice);
	_render = new ShaderColor2D(*this);
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
	
	auto &s1 = _pSwapChain->NextImagePipelineAsync();
	auto &s2 = _render->Draw(s1);
	_pSwapChain->Present(s2);
	


}
