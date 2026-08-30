#pragma once
#include <stdint.h>
#include <string>

enum SamplerAssignmentStrategy {
	ONE_TEXTURE_ASSIGNMENT,
	MERGE_TEXTURES_INTO_ATLAS
};
struct TextureSamplerConfig {
	std::string name;
	unsigned int binding;
	SamplerAssignmentStrategy strategy;
};



class IShaderConfiguration {
	public:
		virtual IShaderConfiguration& SetVerticeShader(const uint32_t* bytecode, uint32_t size)=0;
		virtual IShaderConfiguration& SetFragmentShader(const uint32_t* bytecode, uint32_t size)=0;
		virtual IShaderConfiguration& DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)=0;
		virtual IShaderConfiguration& DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)=0;
		virtual IShaderConfiguration& DeclareTextureSampler(std::string name,unsigned int binding, SamplerAssignmentStrategy strategy) = 0;
};


