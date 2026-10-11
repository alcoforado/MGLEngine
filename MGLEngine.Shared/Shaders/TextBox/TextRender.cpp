#include "TextRender.h"
#include "textRender_frag.h"
#include "textRender_vert.h"


class TextRenderShader :IShader {
public:
	//ShaderConfiguration
	virtual void Init(ShaderConfiguration& config)
	{
		config.DeclareVertexAttribute_FloatVec2("position2d", 0);
		config.DeclareVertexAttribute_FloatVec2("texCoord", 1);
		config.SetVerticeShader(textRender_vert, sizeof(textRender_vert));
		config.SetFragmentShader(textRender_frag, sizeof(textRender_frag));

		config.DeclareTextureSampler("fontSampler", 1, ONE_TEXTURE_ASSIGNMENT);


	}

};


TextRender::TextRender(MGLEngine& engine, glm::vec2 tl, std::string text, std::string fontPath)
:_text(text), _tl(tl)
{
	engine.AddShape<TextRenderShader>(*this, [fontPath](IShapeRegistrationConfig& config) {
		config.BindFont(fontPath, "fontSampler");


		});
}


