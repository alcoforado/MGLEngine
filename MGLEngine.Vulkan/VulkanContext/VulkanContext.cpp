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
#include <MGLEngine.Shared/Painters/CyclicColor.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanFence.h>
#include <MGLEngine.Vulkan\RenderResources\VulkanDescriptorSetPool.h>
VulkanContext::VulkanContext(GLFWwindow * window)
	:_vkLogicalDevice(_vkInstance.GetPhysicalDevices()[0].CreateLogicalDevice(window)),
	_memoryMngr(*_vkLogicalDevice,1),
	_semaphorePool(_vkLogicalDevice)
{
	//Set Swap Chain
	_pSwapChain = new VulkanSwapChain(window,*_vkLogicalDevice);
	_render = new ShaderColor2D(this);
	_drawContext.RenderContext = this;
	_shaders.push_back(_render);
	
	for (int i = 0; i < _pSwapChain->GetImageViews().size();i++)
	{
		PerFrameData *pfd = new PerFrameData(GetLogicalDevice());
		_framesData.push_back(pfd);

	}
	GetLogicalDevice()->GetDescriptorSetPool()->AllocateDescriptorSets();
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
	pFrameData->Commands.clear();
	for(auto sh : _shaders)
	{
		_drawContext.Out.Commands.clear();
		sh->Draw(&_drawContext);
		
		for (auto cb : _drawContext.Out.Commands)
		{
			pFrameData->Commands.push_back(cb);
		}
	}

	//Finally submit the commands
	GetLogicalDevice()->GetGraphicQueue()->Submit(pFrameData->Commands, pFrameData->pExecutionWaitSemaphore, pFrameData->pAcquireImageSemaphore->GetResource(), { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }, pFrameData->pExecutionFence);
	
	//Append that to the present wireframe command
	GetSwapChain()->Present(pFrameData->pExecutionWaitSemaphore);

	GetLogicalDevice()->WaitToBeIdle();
	//Present the next frame


}
