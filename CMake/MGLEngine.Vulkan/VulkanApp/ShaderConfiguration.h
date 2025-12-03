#include <MGLEngine.Shared/Shaders/IShaderConfiguration.h>

struct ShaderByteCode {
	uint32_t* byteCode;
	uint32_t size;
	ShaderByteCode() {}
};

struct VertexAttribute {
	std::string name;
	uint32_t location;
	uint32_t size;
	VkFormat format;
	uint32_t offset;
};


class ShaderConfiguration: public IShaderConfiguration {

	uint32_t currentOffset = 0;
	public: //data
	
		ShaderByteCode verticeShader;
		ShaderByteCode fragmentShader;
		std::vector<VertexAttribute> vertexAttributes;

	public: //Aux Methods
		uint32_t GetTotalAttributesSize() const
		{
			return currentOffset;
		}
	
	public: //virtual overrides for IShaderConfiguration 
		void SetVerticeShader(uint32_t* bytecode, uint32_t size)
		{
			verticeShader.byteCode = bytecode;
			verticeShader.size = size;
		}
		void SetFragmentShader(uint32_t* bytecode, uint32_t size)
		{
			fragmentShader.byteCode = bytecode;
			fragmentShader.size = size;
		}

	

		void DeclareVertexAttribute_FloatVec4(std::string name, uint32_t location)
		{
			VertexAttribute attr = {
				.name = name,
				.location = location,
				.size = 16,
				.format = VK_FORMAT_R32G32B32A32_SFLOAT,
				.offset = currentOffset
			};
			currentOffset += attr.size;
			vertexAttributes.push_back(attr);
		}
		void DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)
		{
			VertexAttribute attr = {
				.name = name,
				.location = location,
				.size = 8,
				.format = VK_FORMAT_R32G32B32_SFLOAT,
				.offset = currentOffset

			};
			currentOffset += attr.size;
			vertexAttributes.push_back(attr);
		}

};