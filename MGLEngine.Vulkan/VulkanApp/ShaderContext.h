#pragma once

#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/ShaderBindingManager.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanBuffer.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBuffer.h>

struct ShapeElement {
	IDrawingObject* pObject;
	ShapeRegistrationConfig config;
	size_t allocatedVertices;
	size_t allocatedIndices;
	size_t startVertex;
	size_t startIndice;
	bool needRedraw;
	ShapeElement(IDrawingObject *pObject,ShapeRegistrationConfig config) {
		this->pObject = pObject;
		this->config = config;
		allocatedVertices = 0;
		allocatedIndices = 0;
		startVertex = 0;
		startIndice = 0;
		needRedraw = false;
	}
};

class VulkanPipelineData {
	public:
		ShaderBindingManager binding;
		VkPipeline handle;
		VkPipelineLayout layout;
	public:
		VulkanPipelineData(VkPipeline pipeline, VkPipelineLayout pipelineLayout,const ShaderBindingManager &bd) {
			this->handle = pipeline;
			this->layout = pipelineLayout;
			this->binding=bd;
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
	std::vector<ShapeElement> _drawGraph;
	VulkanBuffer _vBuffer;
	VulkanBuffer _iBuffer;
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
	
	void AddShape(IDrawingObject* pShape,ShapeRegistrationConfig config)
	{
		_drawGraph.push_back(ShapeElement(pShape,config));
	}
	void DeleteBuffers()
	{
		_vBuffer.Delete();
		_iBuffer.Delete();
	}
	VulkanPipelineData GetPipeline() const {
		return _pipeline;
	}

	ShaderConfiguration& GetShaderConfiguration() { return _options; }
};


