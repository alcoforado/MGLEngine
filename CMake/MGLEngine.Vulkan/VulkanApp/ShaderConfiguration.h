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
};


class ShaderConfiguration {
	ShaderByteCode verticeShader;
	ShaderByteCode fragmentShader;
	std::vector<VertexAttribute> vertexAttributes;

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
			.format = VK_FORMAT_R32G32B32A32_SFLOAT
		};
		vertexAttributes.push_back(attr);
	}
	void DeclareVertexAttribute_FloatVec2(std::string name, uint32_t location)
	{
		VertexAttribute attr = {
			.name = name,
			.location = location,
			.size = 8,
			.format = VK_FORMAT_R32G32B32_SFLOAT
		};
		vertexAttributes.push_back(attr);
	}

};