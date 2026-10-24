#pragma once
#include  <MGLEngine.Shared/Shaders/FieldType.h>
#include <queue>
#include <string>
#include <typeinfo>

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
struct PushConstantConfig {
	std::string name;
	uint32_t dataTypeId;
	size_t size;
};
std::vector<PushConstantConfig> pushConstants;


struct WindowDimensions {
	uint32_t height;
	uint32_t width;
};


class ShaderConfiguration  {

public: //data

	ShaderByteCode verticeShader;
	ShaderByteCode fragmentShader;
	std::vector<VertexAttributeDeclaration> vertexAttributes;
	std::vector<TextureSamplerConfig> samplers;
	std::vector<PushConstantConfig> pushConstants;
	std::string name;
	bool enableCulling = true;

public: // s for IShaderConfiguration 
	ShaderConfiguration() {}

	// Disable for geometry that should be visible from either side.
	ShaderConfiguration& EnableCulling(bool enabled)
	{
		enableCulling = enabled;
		return *this;
	}

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
	 template<typename T>
	 ShaderConfiguration& DeclarePushContanst(std::string name, unsigned int binding)
	 {
		 auto index = typeId(T).hash_code();
		 auto pushConstant = PushConstantConfig{
			 .name=name,
			 .size=sizeof(T),
			 .
		 }
	 }


	 WindowDimensions GetWindowSize();
	 





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
