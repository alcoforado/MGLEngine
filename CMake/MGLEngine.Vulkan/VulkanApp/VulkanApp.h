#include <vma/vk_mem_alloc.h>
#include <functional>
#include <memory>
#include  <MGLEngine.Vulkan/Window/MWindow.h>
#include <MGLEngine.Vulkan/VulkanApp/VulkanConfiguration.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanInstance.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanPhysicalDevice.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanSurface.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include  "SwapChainData.h"
#include <unordered_map>
#include "ShaderContext.h"
 namespace MGL {
	class VulkanApp {
		private:
			MGL::Window* _pWindow=nullptr;
			VulkanInstance* _pVulkanInstance=nullptr;
			const VulkanPhysicalDevice* _pPhysicalDevice = nullptr; //Active physical device
			VulkanSurface* _pVulkanSurface=nullptr;
			VulkanLogicalDevice* _pLogicalDevice=nullptr;
			std::unordered_map<std::string, ShaderContext> _shaders;
			int _graphicQueueIndex;
			SwapChainData _swapChain;
			VmaAllocator _allocator;
			VkRenderPass _vkRenderPass;
			
			//configuraion options
			WindowOptions _windowOptions;
			VulkanConfiguration _vulkanConfiguration;

		private:
			void ChoosePhysicalDevice();
			void CreateVulkanSurface();
			void CreateQueues();
			void CreateSwapChain();
			void CreateSwapChainImageViews();
			void CreateRenderPass();
			void CreateFramebuffers();
			void CreateVulkanMemoryAllocator();
			void InitShaders();

		private:
			VkPipeline CreatePipeline(const ShaderConfiguration& config);
			std::vector<VkVertexInputBindingDescription> CreatePipelineVertexInputBinding(const ShaderConfiguration& config);
			std::vector<VkVertexInputAttributeDescription> CreatePipelineVertexInputAttributes(const ShaderConfiguration& config);
			
			VkShaderModule CreatePipelineShader(ShaderByteCode byteCode);
			VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
		public:
			void WindowConfig(std::function<void(WindowOptions&)>& config)
			{
				config(_windowOptions);
			}

			void VulkanConfig(std::function<void(IAppConfiguration&)>& config)
			{
				config(_vulkanConfiguration);
			}

			VulkanApp();
		
			~VulkanApp();
			void Init();
			
	};
}