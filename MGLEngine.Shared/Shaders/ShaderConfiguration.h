#pragma once
#include  <MGLEngine.Shared/Shaders/FieldType.h>
#include <queue>
#include <string>
struct ShaderByteCode {
	const uint32_t* byteCode;
	uint32_t size;
	ShaderByteCode() {
		byteCode = nullptr;
		size = 0;
	}
};

struct VertexAttributeDeclaration {
	std::string name;
	uint32_t location;
	FieldType type;
};

enum SamplerAssignmentStrategy {
	ONE_TEXTURE_ASSIGNMENT,
	MERGE_TEXTURES_INTO_ATLAS
};
struct TextureSamplerConfig {
	std::string name;
	unsigned int binding;
	SamplerAssignmentStrategy strategy;
};

class ShaderConfiguration  {

public: //data

	ShaderByteCode verticeShader;
	ShaderByteCode fragmentShader;
	std::vector<VertexAttributeDeclaration> vertexAttributes;
	std::vector<TextureSamplerConfig> samplers;
	std::string name;

public: // s for IShaderConfiguration 
	ShaderConfiguration() {}

	 ShaderConfiguration& SetName(std::string name)
	{
		this->name = name;
		return *this;
	}

	 ShaderConfiguration& SetVerticeShader(const uint32_t* bytecode, uint32_t size) 
	{
		verticeShader.byteCode = bytecode;
		verticeShader.size = size;
		return *this;
	}
	 ShaderConfiguration& SetFragmentShader(const uint32_t* bytecode, uint32_t size) 
	{
		fragmentShader.byteCode = bytecode;
		fragmentShader.size = size;
		return *this;
	}

	 ShaderConfiguration& DeclareTextureSampler(std::string name, unsigned int binding, SamplerAssignmentStrategy strategy) 
	{
		TextureSamplerConfig config = TextureSamplerConfig{
			.name = name,
			.binding = binding,
			.strategy = strategy
		};
		samplers.push_back(config);
		return *this;

	}






	 ShaderConfiguration& DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)
	{
		VertexAttributeDeclaration attr = {
			.name = name,
			.location = location,
			.type = TYPE_VEC_FLOAT_4
		};
		vertexAttributes.push_back(attr);
		return *this;
	}
	 ShaderConfiguration& DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)
	{
		VertexAttributeDeclaration attr = {
			.name = name,
			.location = location,
			.type = TYPE_VEC_FLOAT_2
		};
		vertexAttributes.push_back(attr);
		return *this;
	}

};