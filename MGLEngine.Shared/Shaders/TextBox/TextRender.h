#pragma once
#include <MGLEngine.Shared/MGLEngine.h>

class TextRender : IDrawingObject {
	float _width, _height;
	glm::vec2 _tl;
	std::string _text;
	
public:
	
	TextRender(MGLEngine& engine, glm::vec2 tl, std::string text, std::string fontPath);
	
	virtual uint32_t NVertices() override {
		return 4;
	}
	virtual uint32_t NIndices() override {
		return 6;
	}

	virtual void RenderData(RenderSerializationContext& context) override
	{
		auto& posStream = context.GetVerticeAttribute("position2d");
		auto& texStream = context.GetVerticeAttribute("texCoord");
		auto& indexStream = context.GetIndicesStream();

	

	}

	virtual void Draw(IDrawContext& ctx) override
	{
		ctx.DrawIndexed();
	}
	virtual ~TextRender() {}

	



};