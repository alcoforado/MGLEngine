#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>


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
public:
	ShaderConfiguration options;
	VkPipeline pipeline;
	std::vector<DrawElementContext> drawGraph;
	VulkanBuffer vBuffer;
	bool needSerialize;
	BindingManager Binding;
	size_t totalVertices;
	size_t totalIndices;
	ShaderContext() {
		pipeline = VK_NULL_HANDLE;
		needSerialize = true;
	}

};


