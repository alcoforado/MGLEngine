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
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>

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
			VulkanMemoryAllocator* _pMemoryAllocator = nullptr;
			std::map<std::type_index, ShaderContext> _shaders;
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

		private:
			VkPipeline CreatePipeline(const ShaderConfiguration& config);
			std::vector<VkVertexInputBindingDescription> CreatePipelineVertexInputBinding(BindingManager &binding);
			std::vector<VkVertexInputAttributeDescription> CreatePipelineVertexInputAttributes(BindingManager &binding);
			
			VkShaderModule CreatePipelineShader(ShaderByteCode byteCode);
			VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
		protected: //IMGLEngine implementation
			virtual void RegisterShader(std::unique_ptr<IShader> pShader) override;
			virtual bool IsShaderRegistered(const std::type_index shaderType) override;
			virtual void AddShape(const std::type_index shaderTypeIndex, IDrawingObject& shape) override;
		public:
			VkFormat ToVkFormat(enum FieldType type);

			~VulkanEngine();
		
			VulkanEngine(WindowOptions woptions,AppConfiguration coptions);
			
			
			void Draw() override;
	};
}