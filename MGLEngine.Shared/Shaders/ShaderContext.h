#pragma once

#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/VerticeDataLayout.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>

class IGraphicLibrary;
struct ShapeElement {
	IDrawingObject* pObject;
	ShapeRegistrationConfig config;
	size_t allocatedVertices;
	size_t allocatedIndices;
	size_t startVertex;
	size_t startIndice;
	bool needRedraw;
	ShapeElement(IDrawingObject* pObject, ShapeRegistrationConfig config) {
		this->pObject = pObject;
		this->config = config;
		allocatedVertices = 0;
		allocatedIndices = 0;
		startVertex = 0;
		startIndice = 0;
		needRedraw = false;
	}
};

struct SerializationResult {
	bool NeedResize;
	bool Written;
	size_t VerticeDataSizeInBytes;
	size_t IndexDataSizeInBytes;
};

class IMemoryProvider {

};

class ShaderContext {



private:
	ShaderConfiguration _options;
	std::vector<ShapeElement> _drawGraph;
	bool _needSerialize;
	bool _needResize;
	VerticeDataLayout _verticeDataLayout;
	size_t _totalVertices;
	size_t _totalIndices;
	std::string _name;
	size_t _index;
public:
	GLID glId;

	

	ShaderContext(size_t index, ShaderConfiguration options);

	size_t GetIndex() const { return _index; }
	size_t GetTotalVertices() const { return _totalVertices; }
	const std::vector<ShapeElement>& GetDrawingElements() const { return _drawGraph; }
	ShaderContext() {
		_index = 0;
		_needSerialize = true;
		_needResize = true;
		_totalVertices = 0;
		_totalIndices = 0;
	}

	void DeclareShaderBindings(GlobalBindingsTable& tbl);
	void BindShapeResources(GlobalBindingsTable& tbl);
	const VerticeDataLayout& GetVerticeDataLayout() { return _verticeDataLayout; }
	SerializationResult Serialize(uint8_t* pVertice, size_t verticeSize, uint8_t* pIndex, size_t indexSizeInBytes);
	
	//void WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer);

	void AddShape(IDrawingObject* pShape, ShapeRegistrationConfig config)
	{
		_drawGraph.push_back(ShapeElement(pShape, config));
	}
	
	

	ShaderConfiguration& GetShaderConfiguration() { return _options; }
};


