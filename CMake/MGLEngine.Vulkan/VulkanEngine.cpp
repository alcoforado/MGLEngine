#include "VulkanEngine.h"
#include<algorithm>
#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>
#include <MGLEngine.Shared/Utils/utils.h>
#include <MGLEngine.Shared/Utils/eassert.h>
using namespace MGL;



MGL::VulkanEngine::VulkanEngine(WindowOptions woptions, AppConfiguration coptions)
	: _windowOptions(woptions), _vulkanConfiguration(coptions)
{
	_pWindow = new Window(_windowOptions);
	_pVulkanInstance = new VulkanInstance(
		_vulkanConfiguration.Name,
		_vulkanConfiguration.EnableDebug);
	ChoosePhysicalDevice();
	CreateVulkanSurface();
	CreateQueues();
	CreateSwapChain();
	CreateRenderPass();
	CreateFramebuffers();
	CreateSemaphores();
}


#pragma region Init Aux Functions
void MGL::VulkanEngine::CreateVulkanSurface() {
	_pVulkanSurface = new VulkanSurface(_pVulkanInstance, _pWindow);
}

void MGL::VulkanEngine::CreateQueues() {
	int32_t graphicQueueIndex = _pPhysicalDevice->FindQueueFamilyIndex([](auto family) {
		return family.IsGraphic && family.SupportPresentation;
		});
	if (graphicQueueIndex == -1) {
		throw new Exception("No suitable graphic queue found that supports presentation.");
	}
	_pLogicalDevice = new VulkanLogicalDevice(*_pPhysicalDevice, graphicQueueIndex);


}

void MGL::VulkanEngine::CreateSwapChain() {

	VulkanSwapChainOptions options{
		.NBuffers = _vulkanConfiguration.SwapChainSize,
		.VSync = _vulkanConfiguration.VSync,
	};
	_pSwapChain = new VulkanSwapChain(*_pVulkanSurface, *_pLogicalDevice, options);

}

void MGL::VulkanEngine::CreateCommandBuffer()
{
	_pCommandBuffer = _pCommandPool->CreateCommandBuffer();
}



void MGL::VulkanEngine::CreateRenderPass()
{
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = _pSwapChain->GetImageFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;


	//Specify that  the dst Subpass (The only subpass We defined) will wait for the external subpass to finish
	//It will wait for the external souce to finish the color attachment output stage
	//before it can access the same stage
	VkSubpassDependency dependency{};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstSubpass = 0;             
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo passInfo{};
	passInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	passInfo.attachmentCount = 1;
	passInfo.pAttachments = &colorAttachment;
	passInfo.subpassCount = 1;
	passInfo.pSubpasses = &subpass;
	passInfo.dependencyCount = 1;
	passInfo.pDependencies = &dependency;
	vkCreateRenderPass(_pLogicalDevice->GetHandle(), &passInfo, nullptr, &_vkRenderPass);
}

void MGL::VulkanEngine::CreateFramebuffers() {
	auto imageViews = _pSwapChain->GetImageViews();
	for (auto imageView : imageViews) {
		VkImageView attachments[] = {
			imageView
		};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = _vkRenderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _pSwapChain->GetExtent2D().width;
		framebufferInfo.height = _pSwapChain->GetExtent2D().height;
		framebufferInfo.layers = 1;

		VkFramebuffer framebuffer;
		auto result=vkCreateFramebuffer(_pLogicalDevice->GetHandle(), &framebufferInfo, nullptr, &framebuffer);
		AssertVulkanSuccess(result);
		_framebuffers.push_back(framebuffer);
	}

}

void MGL::VulkanEngine::CreateSemaphores()
{
	_pImageAvailableSemaphore = new VulkanSemaphore(_pLogicalDevice);
	_pRenderFinishedSemaphore = new VulkanSemaphore(_pLogicalDevice);
	_pInFlightFence = new VulkanFence(_pLogicalDevice, true);
}

void MGL::VulkanEngine::CreateCommandPool()
{
	_pCommandPool = new VulkanCommandPool(*_pLogicalDevice);

}

void MGL::VulkanEngine::CreateVulkanMemoryAllocator()
{
	_pMemoryAllocator = new VulkanMemoryAllocator(*_pLogicalDevice);
}

int deviceScore(const VulkanPhysicalDevice& device) {
	int score = 0;
	// Example criteria for scoring
	if (device.IsDiscrete()) {
		score += 5000; // Prefer discrete GPUs
	}
	if (device.IsIntegrated())
	{
		score += 4000;
	}
	if (device.IsCPU()) {
		score += 3000; // Least preferred
	}
	if (device.IsVirtual()) {
		score = +2000;
	}
	if (device.HasComputeQueue()) {
		score += 500;
	}


	return score;
}

void MGL::VulkanEngine::ChoosePhysicalDevice()
{
	auto& v = _pVulkanInstance->GetPhysicalDevices();
	std::vector<int> suitableDevices;
	for (int i = 0; i < v.size(); i++) {
		suitableDevices.push_back(i);

	}
	std::sort(suitableDevices.begin(), suitableDevices.end(), [v](int a, int b) {
		int scoreA = deviceScore(v[a]);
		int scoreB = deviceScore(v[b]);
		if (scoreA == scoreB)
		{
			return v[a].GetProperties().limits.maxImageDimension1D > v[b].GetProperties().limits.maxImageDimension1D;
		}
		return scoreA > scoreB;
		});
	_pPhysicalDevice = &(v[suitableDevices[0]]);
}
#pragma endregion

#pragma region IMGLEngine Implementation
void MGL::VulkanEngine::RegisterShader(std::unique_ptr<IShader> pShader)
{
	eassert(pShader != nullptr, "Shader pointer is null");
	std::type_index typeIndex(typeid(*pShader));
	eassert(_shaders.find(typeIndex) == _shaders.end(), std::format("Shader of type {} already registered", typeIndex.name()));
	ShaderConfiguration options = {};
	pShader->Init(options);
	auto pipeline = CreatePipeline(options);
	auto binding = BindingManager(options.vertexAttributes);
	ShaderContext ctx(pipeline, options, binding);
	this->_shaders[typeIndex] = ctx;
}

bool MGL::VulkanEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shaders.find(shaderType) != _shaders.end();
}

void  MGL::VulkanEngine::AddShape(const std::type_index shaderTypeIndex, IDrawingObject& shape)
{

	eassert(_shaders.contains(shaderTypeIndex), std::format("Shader for object {} was not registered", typeid(shape).name()));
	ShaderContext& ctx = _shaders[shaderTypeIndex];
	ctx.AddShape(&shape);
}
#pragma endregion

#pragma region Shaders Pipeline Creation 

std::vector<VkVertexInputBindingDescription> MGL::VulkanEngine::CreatePipelineVertexInputBinding(BindingManager& bindingManager)
{
	std::vector<VkVertexInputBindingDescription> result;
	result.push_back({
		.binding = 0,
		.stride = (uint32_t)bindingManager.GetStride(),
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
		});
	return result;
}

std::vector<VkVertexInputAttributeDescription> MGL::VulkanEngine::CreatePipelineVertexInputAttributes(BindingManager& binding)
{

	std::vector<VkVertexInputAttributeDescription> result;
	for (const auto& attr : binding.GetVertexAttributes())
	{
		VkVertexInputAttributeDescription elem = {
			.location = attr.location,
			.binding = 0,
			.format = ToVkFormat(attr.type),
			.offset = static_cast<uint32_t>(attr.offset)
		};
		result.push_back(elem);
	}
	return result;
}

VkShaderModule VulkanEngine::CreatePipelineShader(ShaderByteCode byteCode)
{
	VkShaderModule result;
	VkShaderModuleCreateInfo shaderMod = {};
	shaderMod.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderMod.codeSize = byteCode.size;
	shaderMod.pCode = byteCode.byteCode;
	auto err = vkCreateShaderModule(_pLogicalDevice->GetHandle(), &shaderMod, nullptr, &result);
	AssertVulkanSuccess(err);
	return result;

}


VkFormat MGL::VulkanEngine::ToVkFormat(enum FieldType type)
{
	VkFormat tbl[4];
	tbl[TYPE_UINT] = VK_FORMAT_R32_UINT;
	tbl[TYPE_FLOAT] = VK_FORMAT_R32_SFLOAT;
	tbl[TYPE_VEC_FLOAT_2] = VK_FORMAT_R32G32_SFLOAT;
	tbl[TYPE_VEC_FLOAT_4] = VK_FORMAT_R32G32B32A32_SFLOAT;
	eassert(type < 4, "Field Type conversion not supported");
	return tbl[type];

}

VulkanPipelineData VulkanEngine::CreatePipeline(const ShaderConfiguration& config)
{


	VkPipelineShaderStageCreateInfo VertShaderStageInfo = {};
	VertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	VertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	VertShaderStageInfo.module = CreatePipelineShader(config.verticeShader);
	VertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo FragShaderStageInfo = {};
	FragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	FragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	FragShaderStageInfo.module = CreatePipelineShader(config.fragmentShader);
	FragShaderStageInfo.pName = "main";

	std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;
	ShaderStages.push_back(VertShaderStageInfo);
	ShaderStages.push_back(FragShaderStageInfo);




	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	InputAssembly = {};
	InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssembly.primitiveRestartEnable = VK_FALSE;

	//Set Viewport

	VkViewport Viewport = {};
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width = static_cast<float>(_pSwapChain->GetExtent2D().width);
	Viewport.height = static_cast<float>(_pSwapChain->GetExtent2D().height);
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	VkRect2D Scissor = {};
	Scissor.offset = { 0, 0 };
	Scissor.extent = _pSwapChain->GetExtent2D();

	VkPipelineViewportStateCreateInfo ViewportState = {};
	ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportState.viewportCount = 1;
	ViewportState.pViewports = &Viewport;
	ViewportState.scissorCount = 1;
	ViewportState.pScissors = &Scissor;


	VkPipelineRasterizationStateCreateInfo Rasterizer = {};
	Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	Rasterizer.depthClampEnable = VK_FALSE;
	Rasterizer.rasterizerDiscardEnable = VK_FALSE;
	Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	Rasterizer.lineWidth = 1.0f;
	Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	Rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	Rasterizer.depthBiasEnable = VK_FALSE;
	Rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	Rasterizer.depthBiasClamp = 0.0f; // Optional
	Rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	VkPipelineMultisampleStateCreateInfo Multisampling = {};
	Multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	Multisampling.sampleShadingEnable = VK_FALSE;
	Multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	Multisampling.minSampleShading = 1.0f; // Optional
	Multisampling.pSampleMask = nullptr; /// Optional
	Multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	Multisampling.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineColorBlendAttachmentState ColorBlendAttachment = {};
	ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColorBlendAttachment.blendEnable = VK_FALSE;
	ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

	VkPipelineColorBlendStateCreateInfo ColorBlending = {};
	ColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlending.logicOpEnable = VK_FALSE;
	ColorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	ColorBlending.attachmentCount = 1;
	ColorBlending.pAttachments = &ColorBlendAttachment;
	ColorBlending.blendConstants[0] = 0.0f; // Optional
	ColorBlending.blendConstants[1] = 0.0f; // Optional
	ColorBlending.blendConstants[2] = 0.0f; // Optional
	ColorBlending.blendConstants[3] = 0.0f; // Optional

	//
	VkPipelineVertexInputStateCreateInfo _pipelineVertexInputState = {};
	BindingManager binding(config.vertexAttributes);
	auto bindingDescriptions = CreatePipelineVertexInputBinding(binding);
	auto attributeDescriptions = CreatePipelineVertexInputAttributes(binding);
	_pipelineVertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	_pipelineVertexInputState.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
	_pipelineVertexInputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	_pipelineVertexInputState.pVertexBindingDescriptions = bindingDescriptions.data();
	_pipelineVertexInputState.pVertexAttributeDescriptions = attributeDescriptions.data();

	//PipelineLayout 
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	VkPipelineLayout vkPipelineLayout;
	auto err=vkCreatePipelineLayout(_pLogicalDevice->GetHandle(), &pipelineLayoutInfo, nullptr, &vkPipelineLayout);
	AssertVulkanSuccess(err);



	//Create Pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = static_cast<uint32_t>(ShaderStages.size());
	pipelineInfo.pStages = ShaderStages.data();
	pipelineInfo.pVertexInputState = &_pipelineVertexInputState;
	pipelineInfo.pInputAssemblyState = &InputAssembly;

	pipelineInfo.renderPass = _vkRenderPass;
	pipelineInfo.subpass = 0;


	pipelineInfo.pViewportState = &ViewportState;
	pipelineInfo.pRasterizationState = &Rasterizer;
	pipelineInfo.pMultisampleState = &Multisampling;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &ColorBlending;
	pipelineInfo.pDynamicState = nullptr;
	pipelineInfo.layout = VK_NULL_HANDLE;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	VkPipeline vkPipeline;
	auto err1 = vkCreateGraphicsPipelines(_pLogicalDevice->GetHandle(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &vkPipeline);
	AssertVulkanSuccess(err1);
	return VulkanPipelineData(vkPipeline, vkPipelineLayout);
}


#pragma endregion

void MGL::VulkanEngine::Draw()
{
	_pInFlightFence->Wait();
	_pInFlightFence->Reset();
	
	uint32_t imageIndex = _pSwapChain->NextImagePipelineAsync(_pImageAvailableSemaphore);
	

	(*_pCommandBuffer)
		.Reset()
		.Begin()
		.BeginRenderPass(_vkRenderPass, _framebuffers[imageIndex], _pSwapChain->GetExtent2D(), glm::vec4(0, 0, 0, 1));
		
	for (auto pair : _shaders)
	{
		ShaderContext& ctx = pair.second;
		ctx.Serialize(*(this->_pMemoryAllocator));
		ctx.WriteCommandBuffer(*_pCommandBuffer);
	}
	_pCommandBuffer->EndRenderPass();
	_pCommandBuffer->End();
	_pLogicalDevice->GetGraphicQueue()->Submit(
		_pCommandBuffer,
		_pRenderFinishedSemaphore, //signal when finished
		_pImageAvailableSemaphore, //wait on
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, //stage to wait
		_pInFlightFence //fence to signal		
	);
	_pLogicalDevice->GetGraphicQueue()->Present(_pSwapChain->GetHandle(), imageIndex, _pRenderFinishedSemaphore);
}

void MGL::VulkanEngine::Run() {
	auto glfwWindow = _pWindow->GLFWHandler();
	while (glfwWindowShouldClose(glfwWindow))
	{
		glfwPollEvents();
		Draw();
	}
}

#pragma region Cleanup
MGL::VulkanEngine::~VulkanEngine() {
	if (_pCommandPool)
		delete _pCommandPool;
	DestroyFramebuffer();
	DestroyPipelines();
	DestroyRenderPass();
	if (_pSwapChain)
		delete _pSwapChain;
	DestroyVulkanMemoryAllocator();
	DestroySyncObjects();
	if_free(_pLogicalDevice);
	if_free(_pVulkanSurface);
	if_free(_pVulkanInstance);
	if_free(_pWindow);
	// Destructor implementation (if needed)
}

void MGL::VulkanEngine::DestroySyncObjects() {
	if_free(_pInFlightFence);
	if_free(_pRenderFinishedSemaphore);
	if_free(_pImageAvailableSemaphore);
	
}

void MGL::VulkanEngine::DestroyPipelines()
{
	for (auto& pair : _shaders)
	{
		ShaderContext& ctx = pair.second;
		vkDestroyPipeline(_pLogicalDevice->GetHandle(), ctx.GetPipeline().handle, nullptr);
		vkDestroyPipelineLayout(_pLogicalDevice->GetHandle(), ctx.GetPipeline().layout, nullptr);
	}
	
}

void MGL::VulkanEngine::DestroyRenderPass()
{
		vkDestroyRenderPass(_pLogicalDevice->GetHandle(), _vkRenderPass, nullptr);

}


void MGL::VulkanEngine::DestroyFramebuffer()
{
	for (size_t i = 0; i < _framebuffers.size(); i++) {
		vkDestroyFramebuffer(_pLogicalDevice->GetHandle(), _framebuffers[i], nullptr);
	}
}

void MGL::VulkanEngine::DestroyVulkanMemoryAllocator()
{
	if (_pMemoryAllocator)
	{
		delete _pMemoryAllocator;
	}
}

#pragma endregion 