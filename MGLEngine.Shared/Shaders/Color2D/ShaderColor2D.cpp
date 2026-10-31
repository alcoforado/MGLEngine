#include "ShaderColor2D.h"
#include <glm/glm.hpp>
#include <MGLEngine.Shared/Shaders/BindingConstants.h>
void ShaderColor2D::Init(ShaderConfiguration& config)
{
	config.EnableCulling(false);
	config.DeclareVertexAttribute_FloatVec4("color", 1);
	config.DeclareVertexAttribute_FloatVec2("position2d", 0);
	config.SetVerticeShader(color2D_vert, sizeof(color2D_vert));
	config.SetFragmentShader(color2D_frag, sizeof(color2D_frag));
	config.DeclareMappedUbo<glm::mat2>("matrix2D", FrequencyUsage::PER_FRAME, Bindings::COLOR2D_MATRIX, ShaderStage::VERTEX_STAGE, glm::mat2(1.0));

}
		
