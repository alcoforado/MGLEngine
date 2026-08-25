#pragma once
#include <MGLEngine.Shared/Interfaces/IShaderConfiguration.h>
#include  <MGLEngine.Shared/Shaders/FieldType.h>
#include <queue>
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

class ShaderConfiguration: public IShaderConfiguration {

	public: //data
	
		ShaderByteCode verticeShader;
		ShaderByteCode fragmentShader;
		std::vector<VertexAttributeDeclaration> vertexAttributes;
		std::vector<TextureSamplerConfig> samplers;
		std::string name;
	
	public: //virtual overrides for IShaderConfiguration 
		ShaderConfiguration() {}

		virtual IShaderConfiguration& SetName(std::string name)
		{
			this->name = name;
			return *this;
		}

		virtual IShaderConfiguration& SetVerticeShader(const uint32_t* bytecode, uint32_t size) override
		{
			verticeShader.byteCode = bytecode;
			verticeShader.size = size;
			return *this;
		}
		virtual IShaderConfiguration& SetFragmentShader(const uint32_t* bytecode, uint32_t size) override
		{
			fragmentShader.byteCode = bytecode;
			fragmentShader.size = size;
			return *this;
		}

		virtual IShaderConfiguration& DeclareTextureSampler(std::string name, unsigned int binding) override
		{
			TextureSamplerConfig config  = TextureSamplerConfig {
				.name = name,
				.binding=binding
			};
			samplers.push_back(config);
			return *this;

		}

	

		
		virtual IShaderConfiguration& DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)
		{
			VertexAttributeDeclaration attr = {
				.name = name,
				.location = location,
				.type = TYPE_VEC_FLOAT_4
			};
			vertexAttributes.push_back(attr);
			return *this;
		}
		virtual IShaderConfiguration& DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)
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