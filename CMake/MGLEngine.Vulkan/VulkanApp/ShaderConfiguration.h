#pragma once
#include <MGLEngine.Shared/Interfaces/IShaderConfiguration.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>

struct ShaderByteCode {
	const uint32_t* byteCode;
	uint32_t size;
	ShaderByteCode() {}
};



class ShaderConfiguration: public IShaderConfiguration {

	public: //data
	
		ShaderByteCode verticeShader;
		ShaderByteCode fragmentShader;
		std::vector<VertexAttributeDeclaration> vertexAttributes;

	
	public: //virtual overrides for IShaderConfiguration 
		virtual void SetVerticeShader(const uint32_t* bytecode, uint32_t size) override
		{
			verticeShader.byteCode = bytecode;
			verticeShader.size = size;
		}
		virtual void SetFragmentShader(const uint32_t* bytecode, uint32_t size) override 
		{
			fragmentShader.byteCode = bytecode;
			fragmentShader.size = size;
		}

	

		
		virtual void DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)
		{
			VertexAttributeDeclaration attr = {
				.name = name,
				.location = location,
				.type = TYPE_VEC_FLOAT_4
			};
			vertexAttributes.push_back(attr);
		}
		virtual void DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)
		{
			VertexAttributeDeclaration attr = {
				.name = name,
				.location = location,
				.type = TYPE_VEC_FLOAT_2
			};
			vertexAttributes.push_back(attr);
		}

};