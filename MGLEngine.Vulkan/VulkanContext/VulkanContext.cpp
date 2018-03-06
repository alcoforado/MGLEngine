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
	_memoryMngr(*_vkLogicalDevice,2*_MB),
	_semaphorePool(_vkLogicalDevice)
{
	//Set Swap Chain
	_pSwapChain = new VulkanSwapChain(window,*_vkLogicalDevice);
	_render = new ShaderColor2D(*this);
	_drawContext.RenderContext = this;
	_shaders.push_back(_render);
	
	for (int i = 0; i < _pSwapChain->GetImageViews().size();i++)
	{
		PerFrameData *pfd = new PerFrameData(GetLogicalDevice());
		_framesData.push_back(pfd);

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

	for(auto fd: _framesData)
	{
		delete fd;
	}
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

	//We don't know what frame is next so just get the first available semaphore in the pool and use it to 
	//swap the next image
	VulkanSemaphorePool::Handle *sAcquireImage = _semaphorePool.Allocate();
	_pSwapChain->NextImagePipelineAsync(sAcquireImage->GetResource(), nullptr);
	_drawContext.FrameIndex = _pSwapChain->GetCurrentImageIndex();

	//Now we finally have the image index, get the frame data for that index 
	PerFrameData* pFrameData = _framesData[_drawContext.FrameIndex];

	//Wait on the Excution of this frame and then reset it
	pFrameData->pExecutionFence->Wait();
	pFrameData->pExecutionFence->Reset();
	
	//Free the old semaphore used to acquire this frame preveously
	if (pFrameData->pAcquireImageSemaphore != nullptr)
		delete pFrameData->pAcquireImageSemaphore;
	
	//Store the just used semaphore in the frame to be deallocated the next time we revisit this frame
	pFrameData->pAcquireImageSemaphore = sAcquireImage;
	
	//Start asking the shaders classes to input their command buffers
	for(auto sh : _shaders)
	{
		
	}


	
	/*
	frameData.fence->Wait();


	_render->Draw(&_drawContext);
	GetLogicalDevice()->GetGraphicQueue()->Submit(_drawContext.Out.CommandBatch);

	_pSwapChain->Present(_drawContext.Out.EndSignalSemaphore);
	_drawContext.WindowResized = false;
	*/

}
