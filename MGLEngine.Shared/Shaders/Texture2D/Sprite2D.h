#pragma once
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>
#include <MGLEngine.Shared/Shaders/Texture2D/Texture2D.h>

class Sprite2D  : IDrawingObject {
	float _width, _height;
	glm::vec2 _bl;
	public:
		Sprite2D(IMGLEngine& engine, glm::vec2 bl, float width, float height,std::string imgPath)
			:_width(width),_height(height),_bl(bl)
		{
			engine.AddShape<Texture2D>(*this, [imgPath](ShapeRegistrationConfig& config) {
				config.RegisterImage(imgPath);
			});
		}
		virtual uint32_t NVertices() override {
			return 4;
		}
		virtual uint32_t NIndices() override {
			return 6;
		}

		virtual void RenderData(IRenderSerializationContext& context) override
		{
			auto& posStream = context.GetVerticeAttribute("position2d");
			auto& indexStream = context.GetIndicesStream();

			posStream << glm::vec2(_bl.x, _bl.y);
			posStream << glm::vec2(_bl.x + _width, _bl.y);
			posStream << glm::vec2(_bl.x + _width, _bl.y + _height);
			posStream << glm::vec2(_bl.x, _bl.y + _height);

			indexStream << std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3 };



			
		}

		virtual void Draw(IDrawContext& ctx) override
		{
			ctx.DrawIndexed();
		}
		virtual ~Sprite2D() {}



};