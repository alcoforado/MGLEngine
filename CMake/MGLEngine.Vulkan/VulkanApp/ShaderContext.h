#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>

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

class ShaderContext {
private:
	ShaderConfiguration _options;
	VkPipeline _pipeline;
	std::vector<DrawElementContext> _drawGraph;
	VulkanBuffer _vBuffer;
	VulkanBuffer _iBuffer;
	bool _needSerialize;
	bool _needResize;
	BindingManager _binding;
	size_t _totalVertices;
	size_t _totalIndices;
public:
	ShaderContext(VkPipeline pipeline, ShaderConfiguration options, BindingManager bindingManager);
	ShaderContext() {
		_pipeline = VK_NULL_HANDLE;
		_needSerialize = true;
		_needResize = true;
		_totalVertices = 0;
		_totalIndices = 0;
	}
	void Serialize(VulkanMemoryAllocator& vmaAllocator);
	
	void AddShape(IDrawingObject* pShape)
	{
		_drawGraph.push_back(DrawElementContext(pShape));
	}

};


