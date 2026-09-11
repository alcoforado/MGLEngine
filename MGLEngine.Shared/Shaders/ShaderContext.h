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
	ShaderContext(size_t index, ShaderConfiguration options);

	size_t GetIndex() const { return _index; }
	

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
	void Serialize(IGraphicLibrary& gl);

	//void WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer);

	void AddShape(IDrawingObject* pShape, ShapeRegistrationConfig config)
	{
		_drawGraph.push_back(ShapeElement(pShape, config));
	}
	
	

	ShaderConfiguration& GetShaderConfiguration() { return _options; }
};


