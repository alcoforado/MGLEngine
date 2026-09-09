#pragma once
#include <cstddef>
class IGraphicLibrary {
	public:
		virtual void* getVerticeBuffer(int shaderIndex, size_t sizeInBytes)=0;
		virtual void* getIndicesBuffer(int shaderIndex, size_t sizeInBytes)=0;
		virtual void flushVerticeBuffer(int shaderIndex);
		virtual void flushIndicesBuffer(int shaderIndex);
};