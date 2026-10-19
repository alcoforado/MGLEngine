#include "TextBox.h"
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

		config.DeclareTextureSampler("fontSampler", 2, ONE_TEXTURE_ASSIGNMENT);

		
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
		float yBaseline = _tl.y - metaData.Ascender;
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
			tl = glm::vec2(pen.x + glyph.BearingX, yBaseline-glyph.BearingY);
			br = glm::vec2(pen.x + glyph.AdvanceX+kerning.X, tl.y+glyph.Height);
			bl = glm::vec2(tl.x,br.y);
			tr = glm::vec2(br.x,tl.y);
			//start printing the rect
			posStream << tl << bl << br << tr;
			indexStream << 0 << 1 << 2 << 2 << 3 << 0;
			
		}


	
}


