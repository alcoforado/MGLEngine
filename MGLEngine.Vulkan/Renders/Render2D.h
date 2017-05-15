#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
class IRenderContext;

class Render2D
{
	VertexShaderByteCode _vertexByteCode;
	FragmentShaderByteCode _fragShaderCode;
public:
	explicit Render2D(IRenderContext& renderContext);
	~Render2D();
	
};

