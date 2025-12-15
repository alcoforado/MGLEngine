#include "VulkanEngine.h"
#include<algorithm>
#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Vulkan/VulkanUtils.h>

using namespace MGL;
MGL::VulkanEngine::~VulkanEngine() {
	// Destructor implementation (if needed)
}


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
	CreateSwapChainImageViews();
	CreateRenderPass();
	CreateFramebuffers();
	InitShaders();
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
		VkSwapchainCreateInfoKHR createInfo = {};
		auto capabilities = _pLogicalDevice->GetPhysicalDevice().GetCapabilitiesForSurface(*_pVulkanSurface);
		uint32_t imageCount = _vulkanConfiguration.SwapChainSize;
		if (capabilities.minImageCount!=0)
			imageCount = imageCount < capabilities.minImageCount ? capabilities.minImageCount : imageCount;
		if (capabilities.maxImageCount != 0)
			imageCount = imageCount > capabilities.maxImageCount ? capabilities.maxImageCount : imageCount;
		

		//Create Swap Chain
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _pVulkanSurface->GetHandle();
		createInfo.minImageCount = _vulkanConfiguration.SwapChainSize;
		createInfo.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
		createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		createInfo.imageExtent = _pVulkanSurface->GetExtent2D();
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional

		createInfo.preTransform = capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		if (_vulkanConfiguration.VSync)
		{
			createInfo.presentMode = _pLogicalDevice->GetPhysicalDevice().IsPresentModeAvailableForSurface(*_pVulkanSurface, VK_PRESENT_MODE_MAILBOX_KHR) ? VK_PRESENT_MODE_MAILBOX_KHR : VK_PRESENT_MODE_FIFO_KHR;
		}
		else
		{
			createInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

		}
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		_swapChain.imageFormat = createInfo.imageFormat;
		_swapChain.imageColorSpace = createInfo.imageColorSpace;
		_swapChain.dims = createInfo.imageExtent;
		auto err = vkCreateSwapchainKHR(_pLogicalDevice->GetHandle(), &createInfo, nullptr, &(_swapChain.handle));
		AssertVulkanSuccess(err);

		//Implementation moved to constructor

}

void MGL::VulkanEngine::CreateSwapChainImageViews() {
	//Get The imageds handlers
	std::vector<VkImage> images;
	uint32_t imagesCount;
	vkGetSwapchainImagesKHR(_pLogicalDevice->GetHandle(), _swapChain.handle, &imagesCount, nullptr);
	images.resize(imagesCount);
	vkGetSwapchainImagesKHR(_pLogicalDevice->GetHandle(), _swapChain.handle, &imagesCount, images.data());


	//Get images view;
	for (auto img : images)
	{
		VkImageViewCreateInfo createViewInfo = {};
		createViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createViewInfo.image = img;
		createViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createViewInfo.format = _swapChain.imageFormat;
		createViewInfo.flags = 0;
		createViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		//no layers or mipmaps
		createViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createViewInfo.subresourceRange.baseMipLevel = 0;
		createViewInfo.subresourceRange.levelCount = 1;
		createViewInfo.subresourceRange.baseArrayLayer = 0;
		createViewInfo.subresourceRange.layerCount = 1;

		VkImageView view;
		auto err = vkCreateImageView(_pLogicalDevice->GetHandle(), &createViewInfo, nullptr, &view);
		AssertVulkanSuccess(err);
		FrameData frame;
		frame.image = img;
		frame.imageView = view;
		_swapChain.frames.push_back(frame);
	}
}

void MGL::VulkanEngine::CreateRenderPass() 
{
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = _swapChain.imageFormat;
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

	VkRenderPassCreateInfo passInfo{};
	passInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	passInfo.attachmentCount = 1;
	passInfo.pAttachments = &colorAttachment;
	passInfo.subpassCount = 1; 
	passInfo.pSubpasses = &subpass;
	vkCreateRenderPass(_pLogicalDevice->GetHandle(), &passInfo, nullptr, &_vkRenderPass);
}

void MGL::VulkanEngine::CreateFramebuffers() {
	for (size_t i = 0; i < _swapChain.frames.size(); i++) {
		VkImageView attachments[] = {
			_swapChain.frames[i].imageView
		};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = _vkRenderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _swapChain.dims.width;
		framebufferInfo.height = _swapChain.dims.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(_pLogicalDevice->GetHandle(), &framebufferInfo, nullptr, &(_swapChain.frames[i].framebuffer)) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}

void MGL::VulkanEngine::CreateVulkanMemoryAllocator()
{
	VmaAllocatorCreateInfo allocatorCreateInfo = {};
	allocatorCreateInfo.flags = VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT;
	allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_0;
	allocatorCreateInfo.physicalDevice = _pPhysicalDevice->GetHandle();
	allocatorCreateInfo.device = _pLogicalDevice->GetHandle();
	allocatorCreateInfo.instance = _pVulkanInstance->GetHandle();

	VkResult err = vmaCreateAllocator(&allocatorCreateInfo, &_allocator);
	AssertVulkanSuccess(err);
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
	auto &v=_pVulkanInstance->GetPhysicalDevices();
	std::vector<int> suitableDevices;
	for (int i = 0; i < v.size(); i++) {
		suitableDevices.push_back(i);

	}
	std::sort(suitableDevices.begin(),suitableDevices.end(),[v](int a, int b) {
		int scoreA = deviceScore(v[a]);
	    int scoreB=deviceScore(v[b]);
		if (scoreA == scoreB)
		{
			return v[a].GetProperties().limits.maxImageDimension1D > v[b].GetProperties().limits.maxImageDimension1D;
		}
		return scoreA > scoreB;
	});
	_pPhysicalDevice =  &(v[suitableDevices[0]]);
}
#pragma endregion

void MGL::VulkanEngine::InitShaders() {
	for (auto& pair : _vulkanConfiguration.GetShadersMap()) {
		ShaderContext ctx(*pair.second);
		
		
		ShaderConfiguration options = {};
		
		ctx.shader.Init(options);
		ctx.options = options;
		ctx.pipeline = CreatePipeline(options);
		//ctx.vBuffer = CreateVertexBuffer(ctx.GetVerticesDataSize());
		//ctx.Binding = CreateBinding(options);
	}
}

#pragma region Init Shaders Aux Functions


std::vector<VkVertexInputBindingDescription> MGL::VulkanEngine::CreatePipelineVertexInputBinding(BindingManager &bindingManager)
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

VulkanBuffer MGL::VulkanEngine::CreateVertexBuffer(uint64_t sizeInBytes)
{
	VmaAllocationCreateInfo allocInfo = {};
	allocInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

	VkBufferCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	createInfo.size = sizeInBytes;
	createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;


	VkBuffer buffer;
	VmaAllocation allocation;
	VmaAllocationInfo allocInfoResult;
	vmaCreateBuffer(_allocator, &createInfo, &allocInfo, &buffer, &allocation, &allocInfoResult);
	VulkanBuffer vb;
	vb.buffer = buffer;
	vb.size = (uint32_t)sizeInBytes;
	vb.allocation = allocation;
	vb.deviceMemoryTypeIndex = this->_pPhysicalDevice->GetMemoryProperties()[allocInfoResult.memoryType].DeviceLocal;
	return vb;
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

VkPipeline VulkanEngine::CreatePipeline(const ShaderConfiguration& config)
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
	Viewport.width = static_cast<float>(_swapChain.dims.width);
	Viewport.height = static_cast<float>(_swapChain.dims.height);
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	VkRect2D Scissor = {};
	Scissor.offset = { 0, 0 };
	Scissor.extent = _swapChain.dims;

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
	auto bindingDescriptions   = CreatePipelineVertexInputBinding(binding);
	auto attributeDescriptions = CreatePipelineVertexInputAttributes(binding);
	_pipelineVertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	_pipelineVertexInputState.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
	_pipelineVertexInputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	_pipelineVertexInputState.pVertexBindingDescriptions   = bindingDescriptions.data();
	_pipelineVertexInputState.pVertexAttributeDescriptions = attributeDescriptions.data();



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

	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	VkPipeline vkPipeline;
	auto err = vkCreateGraphicsPipelines(_pLogicalDevice->GetHandle(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &vkPipeline);
	AssertVulkanSuccess(err);
	return vkPipeline;
}


#pragma endregion

