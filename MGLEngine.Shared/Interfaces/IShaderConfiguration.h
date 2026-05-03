#pragma once
#include <stdint.h>
#include <string>
class IShaderConfiguration {
	public:
		virtual void SetVerticeShader(const uint32_t* bytecode, uint32_t size)=0;
		virtual void SetFragmentShader(const uint32_t* bytecode, uint32_t size)=0;
		virtual void DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)=0;
		virtual void DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)=0;
};


