#pragma once
#include <cstddef>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <vector>
class IGraphicLibrary {
	public:
		virtual void* GetVerticeBuffer(int shaderIndex, size_t sizeInBytes)=0;
		virtual uint32_t* GetIndicesBuffer(int shaderIndex, size_t sizeInBytes)=0;
		virtual void FlushVerticeBuffer(int shaderIndex)=0;
		virtual void FlushIndicesBuffer(int shaderIndex)=0;
		virtual void Run(std::vector<ShaderContext>& shaders,GlobalBindingsTable& bindingTable) = 0;
};