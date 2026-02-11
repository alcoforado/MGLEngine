#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <MGLEngine.Vulkan/RenderPipeline/VulkanCommandBuffer.h>
struct DrawElementContext {
	IDrawingObject* pObject;
	size_t allocatedVertices;
	size_t allocatedIndices;
	size_t startVertex;
	size_t startIndice;
	bool needRedraw;
	DrawElementContext(IDrawingObject *pObject) {
		this->pObject = pObject;
		allocatedVertices = 0;
		allocatedIndices = 0;
		startVertex = 0;
		startIndice = 0;
		needRedraw = false;
	}
};

class VulkanPipelineData {
public:
	VkPipeline handle;
	VkPipelineLayout layout;
public:
	VulkanPipelineData(VkPipeline pipeline, VkPipelineLayout pipelineLayout) {
		this->handle = pipeline;
		this->layout = pipelineLayout;
	}
	VulkanPipelineData() {
		handle = VK_NULL_HANDLE;
		layout = VK_NULL_HANDLE;	
	}
	

	

};

class ShaderContext {



private:
	ShaderConfiguration _options;
	VulkanPipelineData _pipeline;
	std::vector<DrawElementContext> _drawGraph;
	VulkanBuffer _vBuffer;
	VulkanBuffer _iBuffer;
	bool _needSerialize;
	bool _needResize;
	BindingManager _binding;
	size_t _totalVertices;
	size_t _totalIndices;
public:
	ShaderContext(VulkanPipelineData pipeline, ShaderConfiguration options, BindingManager bindingManager);
	ShaderContext() {
		_needSerialize = true;
		_needResize = true;
		_totalVertices = 0;
		_totalIndices = 0;
	}
	void Serialize(VulkanMemoryAllocator& vmaAllocator);

	void WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer);
	
	void AddShape(IDrawingObject* pShape)
	{
		_drawGraph.push_back(DrawElementContext(pShape));
	}
	VulkanPipelineData GetPipeline() const {
		return _pipeline;
	}
};


