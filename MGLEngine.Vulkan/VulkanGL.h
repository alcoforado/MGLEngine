#include <functional>
#include <memory>
#include <MGLEngine.Shared/Window/MWindow.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanInstance.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanPhysicalDevice.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanSurface.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <MGLEngine.Vulkan/VulkanApp/SwapChainData.h>
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
	s_ptr<VulkanBuffer> verticeBuffer; //vertices buffer
	s_ptr<VulkanBuffer> indicesBuffer;
};




struct VulkanUbo {
	s_ptr<VulkanBuffer> pBuffer;
	
	
};

struct VulkanImageData {
	s_ptr<VulkanImage> image;
	VkImageView view;
};

 namespace MGL {
	class VulkanGL: public IGraphicLibrary  {
		private:
			unsigned _numberOfDescriptorSets;
			s_ptr<MWindow> _pWindow=nullptr;
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
			
			VulkanSemaphore* _pImageAvailableSemaphore;
			VulkanFence* _pInFlightFence = nullptr;
			AppConfiguration _vulkanConfiguration;
			VkDescriptorPool _descriptorPool = VK_NULL_HANDLE;
			VkDescriptorSetLayout _descriptorSetLayout = VK_NULL_HANDLE;
			std::vector<VulkanSemaphore*> _pRenderFinishedSemaphore;
			std::vector<VkFramebuffer> _framebuffers;
			std::vector<VkDescriptorSet> _vkDescriptorSets;
			std::vector<VkWriteDescriptorSet> _pendingWrites;


			//Vk Resources
			std::vector<VulkanShaderData> _vVulkanShaderData;
			std::vector<VkSampler> _vSamplers;
			std::vector<VulkanImageData> _vImages;
			std::vector<std::vector<VulkanUbo>> _vUbos;  //one vector for each frame

		private:
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
			void CreateBindedResources(GlobalBindingsTable& tbl);
			void CreateDescritorPool(GlobalBindingsTable& tbl);
			void CreateDescriptorSets();
			void UpdateDescriptorSets(GlobalBindingsTable& tbl);
		private: //auxiliary
			VkFormat MapToVulkanFormat(ImageFormat format);
			GLID CreateTextureSampler(const Sampler2DBinding& sampler);
		private:
			void DestroySwapChain();
			void DestroyRenderPass();
			void DestroyFramebuffer();
			void DestroyShaderContexts();
			void DestroySyncObjects();
			void DestroyVulkanMemoryAllocator();
			void DestroyImages();
			void DestroyDescriptorSets();
			

			
			void DestroySamplers();
		private:
			void WriteCommandBuffer(uint32_t frameIndex,ShaderContext& ctx, VulkanCommandBuffer& commandBuffer, MGLContainer& mglContainer);
			void Serialize(ShaderContext& ctx,MGLContainer &mglContainer);

			VulkanPipelineData CreatePipeline(ShaderContext& ctx, GlobalBindingsTable &globalBindingTable);
			std::vector<VkVertexInputBindingDescription> CreatePipelineVertexInputBinding(const VerticeDataLayout &binding);
			std::vector<VkVertexInputAttributeDescription> CreatePipelineVertexInputAttributes(const VerticeDataLayout &binding);
			
			VkShaderModule CreatePipelineShader(ShaderByteCode byteCode);
			VulkanBuffer CreateVertexBuffer(uint64_t sizeInBytes);
			void ResizeSwapChain();
			void Draw(std::vector<ShaderContext> &shaders,MGLContainer &mglContainer);
			
			



			enum GLID_VULKAN_TYPES {
				SAMPLER2D = 0,
				IMAGE=1,
				SHADER_DATA=2,
				UBO=3

			};

			GLID CreateTextureSampler();

		public:
			VulkanGL(s_ptr<MWindow> pWindow,AppConfiguration coptions);

			virtual ~VulkanGL() override;

			//IMGLEngine Implementation
		
			VkFormat ToVkFormat(enum FieldType type);
			


			// Inherited via IGraphicLibrary
			
			GLID LoadTexture(ITexImage& img) override;
			GLID CreateUbo(uint32_t binding, size_t sizeOfDataType) override; 
			void LoadShaders(std::vector<ShaderContext>& shaders, MGLContainer &mglContainer) override;
			void Run(std::vector<ShaderContext>& shaders, MGLContainer& mglContainer) override;
			

			

	};

}
