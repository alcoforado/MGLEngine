#include "ShaderContext.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanMemoryAllocator.h>
#include <vulkan/vulkan.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanContext/RenderSerizalizationContext.h>
ShaderContext::ShaderContext(VkPipeline pipeline, ShaderConfiguration options, BindingManager bindingManager)
{
	this->_pipeline = pipeline;
	this->_options = options;
	this->_binding = bindingManager;
	_needSerialize = true;
	_needResize = true;
	_totalVertices = _totalIndices = 0;
}

void ShaderContext::Serialize(VulkanMemoryAllocator& vmaAllocator)
{
	if (_needResize)
	{
		size_t indicesOff = 0, verticesOff = 0;
		for (auto& drawingContext : _drawGraph)
		{
			IDrawingObject* shape = drawingContext.pObject;
			drawingContext.allocatedIndices = shape->NIndices();
			drawingContext.allocatedVertices = shape->NVertices();
			drawingContext.startIndice = indicesOff;
			drawingContext.startVertex = verticesOff;
			verticesOff += drawingContext.allocatedVertices;
			indicesOff += drawingContext.allocatedIndices;
		}
		_totalVertices = verticesOff;
		_totalIndices = indicesOff;

		_vBuffer = vmaAllocator.CreateVertexBuffer(_totalVertices * _binding.GetStride());
		_iBuffer = vmaAllocator.CreateIndexBuffer(_totalIndices);
	}
	if (_needSerialize)
	{
		uint8_t* pVertice = (uint8_t*) _vBuffer.Map();
		uint8_t* pIndex   = (uint8_t*) _iBuffer.Map();

		eassert(_binding.CheckVerticeBufferAlignment(pVertice), "Severe error address of the vertice buffr is not 32bits aligned");

		//start initializing the vertice attributes' memory streams
		std::map<std::string, InterleavedMemoryStream> memoryStreamsMap;
		
		for (auto& drawingContext : _drawGraph)
		{
			for (auto vAttribute : _binding.GetVertexAttributes())
			{
				InterleavedMemoryStream memoryStream(pVertice + vAttribute.offset, _binding.GetStride(), drawingContext.allocatedVertices, vAttribute.type);
				memoryStreamsMap[vAttribute.name] = memoryStream;
				IndicesMemoryStream indexStream( reinterpret_cast<uint32_t*>(pIndex) + drawingContext.startIndice, drawingContext.allocatedIndices,drawingContext.startIndice);
				RenderSerializationContext renderContext(memoryStreamsMap, indexStream);
				drawingContext.pObject->RenderData(renderContext);
			}
		}
		_vBuffer.Unmap();
		_iBuffer.Unmap();
	}
	
	

	
	_needResize = _needSerialize = false;

}

void ShaderContext::WriteCommandBuffer(VulkanCommandBuffer& cmdBuffer) {
	cmdBuffer.BindGraphicsPipeline(_pipeline);
	cmdBuffer.BindVertexBuffer(_vBuffer.Handle());
	cmdBuffer.BindIndexBuffer(_iBuffer.Handle());

}






