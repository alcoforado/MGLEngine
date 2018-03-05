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
#include <MGLEngine.Vulkan/RenderPipeline/VulkanFence.h>

VulkanContext::VulkanContext(GLFWwindow * window)
	:_vkLogicalDevice(_vkInstance.GetPhysicalDevices()[0].CreateLogicalDevice(window)),
	_memoryMngr(*_vkLogicalDevice,2*_MB)
{
	//Set Swap Chain
	_pSwapChain = new VulkanSwapChain(window,*_vkLogicalDevice);
	_render = new ShaderColor2D(*this);
	_drawContext.RenderContext = this;
	_shaders.push_back(_render);
	
	for (int i = 0; i < _pSwapChain->GetImageViews().size();i++)
	{
		PerFrameData d;
		d.fence = GetLogicalDevice()->CreateFence(true);
		_framesData.push_back(d);

	}
}




void VulkanContext::OnResize(GLFWwindow *window, int newWidth,int newHeight)
{
	_vkLogicalDevice->WaitToBeIdle();
	_pSwapChain.if_free();
	_pSwapChain = new VulkanSwapChain(window,*_vkLogicalDevice);
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
	
	PerFrameData& frameData = _framesData[_drawContext.FrameIndex];
	_pSwapChain->NextImagePipelineAsync(nullptr, frameData.fence);
	_drawContext.FrameIndex = _pSwapChain->GetCurrentImageIndex();


	
	
	
	frameData.fence->Wait();


	_render->Draw(&_drawContext);
	GetLogicalDevice()->GetGraphicQueue()->Submit(_drawContext.Out.CommandBatch);

	_pSwapChain->Present(_drawContext.Out.EndSignalSemaphore);
	_drawContext.WindowResized = false;


}
