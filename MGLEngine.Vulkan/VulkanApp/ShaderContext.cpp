#include "ShaderContext.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <vulkan/vulkan.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanContext/RenderSerializationContext.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanDrawContext.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
ShaderContext::ShaderContext(ShaderConfiguration options, s_ptr<GlobalBindingsTable> pGlobalTable)
	:_binding(options,pGlobalTable)
{

	this->_options = options;
	_pGlobalBindingTable = pGlobalTable;
	_needSerialize = true;
	_needResize = true;
	_totalVertices = _totalIndices = 0;
}

void ShaderContext::BindShapeResources()
{
	for (auto& shape : _drawGraph)
	{
		for (auto& imgAssignment : shape.config.GetImageAssignments())
		{
			_pGlobalBindingTable->AssignImageResource(imgAssignment.samplerName, imgAssignment.filePath);
		}
	}
}

void ShaderContext::Serialize(VulkanMemoryAllocator& vmaAllocator)
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
		_vBuffer = vmaAllocator.CreateVertexBuffer(_totalVertices * _binding.GetStride());
		_iBuffer = vmaAllocator.CreateIndexBuffer(_totalIndices);
	}
	if (_totalVertices == 0)
		return;

	if (_needSerialize)
	{
		uint8_t* pVertice = (uint8_t*) _vBuffer.Map();
		uint8_t* pIndex   = (uint8_t*) _iBuffer.Map();

		eassert(_binding.CheckVerticeBufferAlignment(pVertice), "Severe error address of the vertice buffr is not 32bits aligned");

		//start initializing the vertice attributes' memory streams
		std::map<std::string, InterleavedMemoryStream> memoryStreamsMap;
		
		for (auto& shapeElement : _drawGraph)
		{
			for (auto vAttribute : _binding.GetVertexAttributes())
			{
				InterleavedMemoryStream memoryStream(pVertice+shapeElement.startVertex*_binding.GetStride() + vAttribute.offset, _binding.GetStride(), shapeElement.allocatedVertices, vAttribute.type);
				memoryStreamsMap[vAttribute.name] = memoryStream;
			}
			IndicesMemoryStream indexStream( reinterpret_cast<uint32_t*>(pIndex) + shapeElement.startIndice, shapeElement.allocatedIndices,0);
			RenderSerializationContext renderContext(memoryStreamsMap, indexStream);
			shapeElement.pObject->RenderData(renderContext);
		}
		_vBuffer.Unmap();
		_iBuffer.Unmap();
	}
	
	

	
	_needResize = _needSerialize = false;

}

void ShaderContext::WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer) {
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






