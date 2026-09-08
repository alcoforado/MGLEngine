#pragma once

#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/ShaderBindingManager.h>

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



class ShaderContext {



private:
	ShaderConfiguration _options;
	std::vector<ShapeElement> _drawGraph;
	bool _needSerialize;
	bool _needResize;
	ShaderBindingManager _binding;
	size_t _totalVertices;
	size_t _totalIndices;
	s_ptr<GlobalBindingsTable> _pGlobalBindingTable;
	std::string _name;
public:
	ShaderContext(ShaderConfiguration options, s_ptr<GlobalBindingsTable> pGlobalTable);

	ShaderContext() {
		_needSerialize = true;
		_needResize = true;
		_totalVertices = 0;
		_totalIndices = 0;
	}

	void BindShapeResources(s_ptr<GlobalBindingsTable> pGlobalBindingTable);

	void Serialize(VulkanMemoryAllocator& vmaAllocator);

	void WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer);

	void AddShape(IDrawingObject* pShape, ShapeRegistrationConfig config)
	{
		_drawGraph.push_back(ShapeElement(pShape, config));
	}
	
	

	ShaderConfiguration& GetShaderConfiguration() { return _options; }
};


