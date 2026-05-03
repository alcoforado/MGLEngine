#include "ShaderColor2D.h"

void ShaderColor2D::Init(IShaderConfiguration& config)
{
	config.DeclareVertexAttribute_FloatVec4("color", 1);
	config.DeclareVertexAttribute_FloatVec2("position2d", 0);
	config.SetVerticeShader(color2D_vert, sizeof(color2D_vert));
	config.SetFragmentShader(color2D_frag, sizeof(color2D_frag));

}
		
