#include <MGLEngine.Shared/Interfaces/IMesh.h>
#include <glm/vec2.hpp>
#include <iostream>
class OrthoRect2D : public IMesh {
private:
	glm::vec2 _bl;
	float _width;
	float _height;

public:
	OrthoRect2D(glm::vec2 bl, float width, float height)
	{
		_bl = bl;
		_width = width;
		_height = height;
	}
	virtual ~OrthoRect2D() {}

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

		posStream << glm::vec2(_bl.x       , _bl.y);
		posStream << glm::vec2(_bl.x+_width, _bl.y); 
		posStream << glm::vec2(_bl.x+_width, _bl.y+_height);
		posStream << glm::vec2(_bl.x       , _bl.y+_height);
		
		indexStream << std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3 };
	}
	virtual void Draw(IDrawContext& ctx) override
	{
		ctx.DrawIndexedTriangles();
	}
};