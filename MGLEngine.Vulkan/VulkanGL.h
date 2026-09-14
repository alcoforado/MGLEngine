#include <functional>
#include <memory>
#include  <MGLEngine.Vulkan/Window/MWindow.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanInstance.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanPhysicalDevice.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanSurface.h>
#include  <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include  <MGLEngine.Vulkan/VulkanApp/SwapChainData.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandPool.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanFence.h>
#include <MGLEngine.Shared/MGLEngine.h>
#include <unordered_map>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanSwapChain.h>
#include <MGLEngine.Vulkan/VulkanApp/ByteCodeCollection.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>

struct VulkanPipelineData {
	VkPipeline handle;
	VkPipelineLayout layout;
};
struct VulkanShaderData {
	VulkanPipelineData pipeline;
	VulkanBuffer verticeBuffer; //vertices buffer
	VulkanBuffer indicesBuffer;
};


 namespace MGL {
	class VulkanGL: public IGraphicLibrary  {
		private:
			MGL::Window* _pWindow=nullptr;
			VulkanInstance* _pVulkanInstance=nullptr;
			const VulkanPhysicalDevice* _pPhysicalDevice = nullptr; //Active physical device
			VulkanSurface* _pVulkanSurface=nullptr;
			VulkanLogicalDevice* _pLogicalDevice=nullptr;
			ByteCodeCollection* _pByteCodeCollection = nullptr;
			VulkanMemoryAllocator* _pMemoryAllocator = nullptr;
			VulkanCommandPool*  _pCommandPool=nullptr;
			VulkanCommandBuffer* _pCommandBuffer;
			VulkanSwapChain *_pSwapChain = nullptr;
			VmaAllocator _allocator;
			VkRenderPass _vkRenderPass;
			std::vector<VkFramebuffer> _framebuffers;
			//configuraion options
			std::vector<VulkanShaderData> _vVulkanShaderData;
			WindowOptions _windowOptions;
			VulkanSemaphore* _pImageAvailableSemaphore;
			std::vector<VulkanSemaphore*> _pRenderFinishedSemaphore;
			VulkanFence* _pInFlightFence = nullptr;
			AppConfiguration _vulkanConfiguration;
			VkDescriptorPool _descriptorPool = VK_NULL_HANDLE;
			VkDescriptorSetLayout _descriptorSetLayout = VK_NULL_HANDLE;
			std::vector<VkDescriptorSet> _vkDescriptorSets;


		private:
			void Init(std::vector<ShaderContext>& shaders, GlobalBindingsTable& bindingTable);
			void ChoosePhysicalDevice();
			void CreateVulkanSurface();
			void CreateLogicalDevice();
			void CreateCommandPool();
			void CreateSwapChain();
			void CreateCommandBuffers();
			void CreateRenderPass();
			void CreateFramebuffers();
			void CreateSyncObjects();
			void CreateVulkanMemoryAllocator();
			void CreateDescriptorSetLayout(GlobalBindingsTable& tbl);
			void CreateDescritorPool(GlobalBindingsTable& tbl);
			void CreateDescriptorSets();
			void LoadResources(GlobalBindingsTable& tbl);

			
		private:
			void DestroySwapChain();
			void DestroyRenderPass();
			void DestroyFramebuffer();
			void DestroyShaderContexts();
			void DestroySyncObjects();
			void DestroyVulkanMemoryAllocator();
		private:
			void WriteCommandBuffer(ShaderContext& ctx, VulkanCommandBuffer& commandBuffer);
			VulkanPipelineData CreatePipeline(ShaderContext& ctx);
			std::vector<VkVertexInputBindingDescription> CreatePipelineVertexInputBinding(const VerticeDataLayout &binding);
			std::vector<VkVertexInputAttributeDescription> CreatePipelineVertexInputAttributes(const VerticeDataLayout &binding);
			
			VkShaderModule CreatePipelineShader(ShaderByteCode byteCode);
			VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
			void ResizeSwapChain();
			void InitializePipelines();
		
			void Draw(std::vector<ShaderContext> &shaders);
		public:
			VulkanGL(WindowOptions woptions,AppConfiguration coptions);

			~VulkanGL();

			//IMGLEngine Implementation
		
			VkFormat ToVkFormat(enum FieldType type);
			


			// Inherited via IGraphicLibrary
			void*     GetVerticeBuffer(size_t shaderIndex, size_t sizeInBytes) override;
			uint32_t* GetIndicesBuffer(size_t shaderIndex, size_t nElements) override;
			void FlushVerticeBuffer(size_t shaderIndex) override;
			void FlushIndicesBuffer(size_t shaderIndex) override;
			size_t LoadTexture(TexImage& img) override;
			void Run(std::vector<ShaderContext>& shaders, GlobalBindingsTable& bindingTable) override;
			
	};
}