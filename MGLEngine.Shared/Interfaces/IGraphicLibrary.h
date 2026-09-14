#pragma once
#include <cstddef>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <MGLEngine.Shared/ResourceLoaders/ImageLoader.h>
#include <vector>
class IGraphicLibrary {
	public:
		virtual void* GetVerticeBuffer(size_t shaderIndex, size_t sizeInBytes)=0;
		virtual uint32_t* GetIndicesBuffer(size_t shaderIndex, size_t sizeInBytes)=0;
		virtual void FlushVerticeBuffer(size_t shaderIndex)=0;
		virtual void FlushIndicesBuffer(size_t shaderIndex)=0;
		virtual size_t LoadTexture(TexImage& img) = 0;
		virtual void Run(std::vector<ShaderContext>& shaders,GlobalBindingsTable& bindingTable) = 0;
};