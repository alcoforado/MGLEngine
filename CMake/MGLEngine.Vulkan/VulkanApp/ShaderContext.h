#include "PipelineOptions.h"
#include <MGLEngine.Shared/Shaders/IShader.h>

struct ShaderByteCode {
	uint32_t* byteCode;
	uint32_t size;
	ShaderByteCode() {}
};


class ShaderContext {
public:
	IShader& shader;
	PipelineOptions options;
	VkPipeline pipeline;

	ShaderByteCode verticeShader;
	ShaderByteCode fragmentShader;
	

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


};


