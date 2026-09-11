#pragma once

#include "ShaderContext.h"
#include <MGLEngine.Shared/Interfaces/RenderSerializationContext.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
ShaderContext::ShaderContext(size_t index,ShaderConfiguration options, s_ptr<GlobalBindingsTable> pGlobalTable)
{
	_index = index;
	_name = options.name;
	this->_options = options;
	_pGlobalBindingTable = pGlobalTable;
	_needSerialize = true;
	_needResize = true;
	_totalVertices = _totalIndices = 0;
}

void ShaderContext::BindShapeResources(s_ptr<GlobalBindingsTable> pGlobalBindingTable)
{
	int i = 1;
	for (auto& shape : _drawGraph)
	{
		std::string ref = std::format("Shader {}, Shape {}", _name, i);
		for (auto& imgAssignment : shape.config.GetImageAssignments())
		{
			pGlobalBindingTable->AssignImageResource(imgAssignment.samplerName, imgAssignment.filePath, ref);
		}
		i++;
	}
}

void ShaderContext::Serialize(IGraphicLibrary& gl)
{
	if (_needResize)
	{
		size_t indicesOff = 0, verticesOff = 0;
		for (auto& shapeElement : _drawGraph)
		{
			IDrawingObject* shape = shapeElement.pObject;
			shapeElement.allocatedIndices = shape->NIndices();
			shapeElement.allocatedVertices = shape->NVertices();
			shapeElement.startIndice = indicesOff;
			shapeElement.startVertex = verticesOff;
			verticesOff += shapeElement.allocatedVertices;
			indicesOff += shapeElement.allocatedIndices;
		}
		_totalVertices = verticesOff;
		_totalIndices = indicesOff;
		if (_totalVertices == 0)
			return;
		
	}
	if (_totalVertices == 0)
		return;

	if (_needSerialize)
	{
		uint8_t* pVertice = (uint8_t*)gl.GetVerticeBuffer(this->_index,_totalVertices * _binding.GetStride());
		uint8_t* pIndex = (uint8_t*) gl.GetIndicesBuffer(this->_index,_totalIndices*sizeof(uint32_t));

		eassert(_binding.CheckVerticeBufferAlignment(pVertice), "Severe error address of the vertice buffr is not 32bits aligned");

		//start initializing the vertice attributes' memory streams
		std::map<std::string, InterleavedMemoryStream> memoryStreamsMap;

		for (auto& shapeElement : _drawGraph)
		{
			for (auto vAttribute : _binding.GetVertexAttributes())
			{
				InterleavedMemoryStream memoryStream(pVertice + shapeElement.startVertex * _binding.GetStride() + vAttribute.offset, _binding.GetStride(), shapeElement.allocatedVertices, vAttribute.type);
				memoryStreamsMap[vAttribute.name] = memoryStream;
			}
			IndicesMemoryStream indexStream(reinterpret_cast<uint32_t*>(pIndex) + shapeElement.startIndice, shapeElement.allocatedIndices, 0);
			RenderSerializationContext renderContext(memoryStreamsMap, indexStream);
			shapeElement.pObject->RenderData(renderContext);
		}
		gl.FlushVerticeBuffer(_index);
		gl.FlushVerticeBuffer(_index);
	}




	_needResize = _needSerialize = false;

}

/*
void VulkanShaderContext::WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer) {
	if (_totalVertices == 0)
		return;
	cmdBuffer.BindGraphicsPipeline(_pipeline.handle);
	cmdBuffer.BindVertexBuffer(_vBuffer.GetHandle());
	cmdBuffer.BindIndexBuffer(_iBuffer.GetHandle());
	for (auto& drawingContext : _drawGraph)
	{
		VulkanDrawContext drawContext(cmdBuffer, drawingContext);
		drawingContext.pObject->Draw(drawContext);

	}

}



*/