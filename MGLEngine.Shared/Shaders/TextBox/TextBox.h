#pragma once
#include <MGLEngine.Shared/MGLEngine.h>

class TextBox : IDrawingObject {
	float _width, _height;
	glm::vec2 _tl;
	std::string _text;
	
public:
	
	TextBox(MGLEngine& engine, glm::vec2 tl, std::string text, std::string fontPath,uint32_t pixelSize);
	
	virtual uint32_t NVertices() override {
		return static_cast<uint32_t>(4*_text.size());
	}

	virtual uint32_t NIndices() override {
		return static_cast<uint32_t>(6*_text.size());
	}

	virtual void RenderData(RenderSerializationContext& context) override;
	

	virtual void Draw(IDrawContext& ctx) override;
	
	virtual ~TextBox() {}

	



};