#include "TextBox.h"
#include "textRender_frag.h"
#include "textRender_vert.h"
#include <MGLEngine.Shared/Utils/numeric_vector_functions.h>

struct TextPushConstant {
	alignas(16) glm::vec4 fontColor;
};
class TextRenderShader :IShader {
public:
	//ShaderConfiguration
	virtual void Init(ShaderConfiguration& config)
	{
		config.EnableCulling(false);
		config.DeclareVertexAttribute_FloatVec2("position2d", 0);
		config.DeclareVertexAttribute_FloatVec2("texCoord", 1);
		config.SetVerticeShader(textRender_vert, sizeof(textRender_vert));
		config.SetFragmentShader(textRender_frag, sizeof(textRender_frag));

		config.DeclareTextureSampler("fontSampler", 2, ONE_TEXTURE_ASSIGNMENT);
		config.DeclarePushConstant<TextPushConstant>("fontColor",1,FRAGMENT_STAGE);
		
	}

};



TextBox::TextBox(MGLEngine& engine, glm::vec2 tl, std::string text, std::string fontPath,  uint32_t pixelSize)
:_text(text), _tl(tl)
{
	engine.AddShape<TextRenderShader>(*this, [fontPath,pixelSize](ShapeRegistrationConfig& config) {
		config.BindFont(fontPath, "fontSampler",pixelSize);


		});
}

void TextBox::RenderData(RenderSerializationContext& context)
{
		auto& posStream = context.GetVerticeAttribute("position2d");
		auto& texStream = context.GetVerticeAttribute("texCoord");
		auto& indexStream = context.GetIndicesStream();
		auto& metaData=context.GetFontMetadata("fontSampler");


		auto wSize = context.WindowSize();
		std::vector<char> str(_text.begin(), _text.end());
		std::array<size_t, 6> indices = { 0,1,2,2,3,0 };
		float toNdcX = 2.0f / wSize.x;
		float toNdcY = 2.0f / wSize.y;
		float yBaseline = _tl.y + toNdcY*metaData.Ascender;
		auto pen = glm::vec2(_tl.x, yBaseline);
		for (size_t i=0;i<str.size();i++)
		{
			bool isLast = i + 1 == str.size();
			char c = str[i];
			
			FontKerning kerning;
			if (!isLast)
				kerning=metaData.GetKerning(c, str[i + 1]);

			auto glyph = metaData.Characters.at(c); 
			
			glm::vec2 tl, br, bl, tr;
			tl = glm::vec2(pen.x + toNdcX*glyph.BearingX, yBaseline-toNdcY*glyph.BearingY);
			br = glm::vec2(pen.x + toNdcX*(glyph.AdvanceX+kerning.X), tl.y+toNdcY*glyph.Height);
			bl = glm::vec2(tl.x,br.y);
			tr = glm::vec2(br.x,tl.y);

			//advance pen
			pen.x = br.x;

						//start printing the rect
			//test
			//posStream << std::vector<float> {-1, -1, -1, 1, 1, 1, 1, -1};
			//texStream << std::vector<float> { 0,  0,  0, 1, 1, 1, 1,  0};
			

			//adjust offset
			indexStream << indices;
			add_offset(indices, (size_t) (4));
			
			posStream << tl << bl << br << tr;
			std::array<float, 8> uv = { 
				glyph.U0, glyph.V0,
				glyph.U0, glyph.V1, 
				glyph.U1, glyph.V1, 
				glyph.U1, glyph.V0 };
			texStream << uv;

			
			
		}


	
}


void TextBox::Draw(IDrawContext& ctx) 
{
	TextPushConstant pc;
	pc.fontColor = glm::vec4(0, 1, 0, 1);
	ctx.PushConstant("fontColor", pc);

	ctx.DrawIndexed();
}


