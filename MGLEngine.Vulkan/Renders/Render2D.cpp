#include "Render2D.h"
#include <vector>
#include "IRenderContext.h"
#include "../shaders/shaders_bytecode.h"

Render2D::Render2D(IRenderContext& renderContext)
{
	VertexShaderByteCode vertexByteCode(renderContext.GetLogicalDevice(),canvas2D_vert,sizeof(canvas2D_vert));
	FragmentShaderByteCode fragShaderCode(renderContext.GetLogicalDevice(), canvas2D_frag, sizeof(canvas2D_frag));
}

Render2D::~Render2D()
{
}
