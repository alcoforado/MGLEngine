#pragma once

#include "ShaderContext.h"
#include <MGLEngine.Shared/Interfaces/RenderSerializationContext.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
ShaderContext::ShaderContext(size_t index,ShaderConfiguration options)
	:_verticeDataLayout(options)
{
	_index = index;
	_name = options.name;
	this->_options = options;
	_needSerialize = true;
	_needResize = true;
	_totalVertices = _totalIndices = 0;
}

void ShaderContext::DeclareShaderBindings(GlobalBindingsTable& tbl)
{
	for (auto& samplerConfig : _options.samplers)
	{
		tbl.AddSampler2D(samplerConfig.binding, samplerConfig.name, _options.name);
	}
}

void ShaderContext::BindShapeResources(GlobalBindingsTable &tbl)
{
	int i = 1;
	for (auto& shape : _drawGraph)
	{
		std::string ref = std::format("Shader {}, Shape {}", _name, i);
		for (auto& imgAssignment : shape.config.GetImageAssignments())
		{
			tbl.AssignImageResource(imgAssignment.samplerName, imgAssignment.filePath, ref);
		}
		i++;
	}
}



SerializationResult ShaderContext::Serialize(uint8_t* pVertice,size_t verticeSizeInBytes,uint8_t *pIndex,size_t indexSizeInBytes)
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
		_needResize = false;
		return SerializationResult{
			.NeedResize=true,
			.Written = false,
			.VerticeDataSizeInBytes=_totalVertices*_verticeDataLayout.GetStride(),
			.IndexDataSizeInBytes  =_totalIndices*sizeof(uint32_t)
		};
		
	}
	if (_totalVertices == 0)
		return SerializationResult{
			.NeedResize = false,
			.Written = false,
			.VerticeDataSizeInBytes=0,
			.IndexDataSizeInBytes = 0
		};

	if (_needSerialize)
	{
		eassert(_totalVertices * _verticeDataLayout.GetStride() <= verticeSizeInBytes, std::format("Vertice Buffer is too small for Shader {}", _name));
		eassert(_totalIndices*sizeof(uint32_t) <= indexSizeInBytes, std::format("Index Buffer is too small for Shader {}", _name));

		

		eassert(_verticeDataLayout.CheckVerticeBufferAlignment(pVertice), "Severe error address of the vertice buffr is not 32bits aligned");

		//start initializing the vertice attributes' memory streams
		std::map<std::string, InterleavedMemoryStream> memoryStreamsMap;

		for (auto& shapeElement : _drawGraph)
		{
			for (auto vAttribute : _verticeDataLayout.GetVertexAttributes())
			{
				InterleavedMemoryStream memoryStream(pVertice + shapeElement.startVertex * _verticeDataLayout.GetStride() + vAttribute.offset, _verticeDataLayout.GetStride(), shapeElement.allocatedVertices, vAttribute.type);
				memoryStreamsMap[vAttribute.name] = memoryStream;
			}
			IndicesMemoryStream indexStream(reinterpret_cast<uint32_t*>(pIndex) + shapeElement.startIndice, shapeElement.allocatedIndices, 0);
			RenderSerializationContext renderContext(memoryStreamsMap, indexStream);
			shapeElement.pObject->RenderData(renderContext);
		}
		_needSerialize = false;
		
	}
	return {
		.NeedResize = false,
		.Written = true,
		.VerticeDataSizeInBytes = verticeSizeInBytes,
		.IndexDataSizeInBytes = indexSizeInBytes
	};
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