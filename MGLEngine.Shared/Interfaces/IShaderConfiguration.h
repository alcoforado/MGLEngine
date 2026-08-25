#pragma once
#include <stdint.h>
#include <string>

struct TextureSamplerConfig {
	std::string name;
	unsigned int binding;
};

class IShaderConfiguration {
	public:
		virtual IShaderConfiguration& SetVerticeShader(const uint32_t* bytecode, uint32_t size)=0;
		virtual IShaderConfiguration& SetFragmentShader(const uint32_t* bytecode, uint32_t size)=0;
		virtual IShaderConfiguration& DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)=0;
		virtual IShaderConfiguration& DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)=0;
		virtual IShaderConfiguration& DeclareTextureSampler(std::string name,unsigned int binding) = 0;
};


