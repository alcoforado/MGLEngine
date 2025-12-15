#include <vma/vk_mem_alloc.h>
#include <functional>
#include <memory>
#include  <MGLEngine.Vulkan/Window/MWindow.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanInstance.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanPhysicalDevice.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanSurface.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <MGLEngine.Shared/Interfaces/IAppBuilder.h>
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>
#include  <MGLEngine.Vulkan/VulkanApp/SwapChainData.h>
#include <unordered_map>
#include <MGLEngine.Vulkan/VulkanApp/ShaderContext.h>
 namespace MGL {
	class VulkanEngine: public IMGLEngine  {
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
			AppConfiguration _vulkanConfiguration;
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
			std::vector<VkVertexInputBindingDescription> CreatePipelineVertexInputBinding(BindingManager &binding);
			std::vector<VkVertexInputAttributeDescription> CreatePipelineVertexInputAttributes(BindingManager &binding);
			
			VkShaderModule CreatePipelineShader(ShaderByteCode byteCode);
			VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
		public:
			VkFormat ToVkFormat(enum FieldType type);

			~VulkanEngine();
		
			VulkanEngine(WindowOptions woptions,AppConfiguration coptions);
			
			
			
	};
}