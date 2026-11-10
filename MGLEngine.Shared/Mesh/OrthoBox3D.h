#pragma once
#include <MGLEngine.Shared/Interfaces/IMesh3D.h>
#include <array>
#include <glm/vec3.hpp>

class OrthoBox3D : public IMesh3D {
private:
	glm::vec3 _origin;
	float _width;
	float _height;
	float _depth;

public:
	

	// The origin is the minimum corner; dimensions extend along +X, +Y and +Z.
	OrthoBox3D(glm::vec3 origin, float width, float height, float depth)
		:_origin(origin), _width(width), _height(height), _depth(depth)
	{
		eassert(width > 0.0f && height > 0.0f && depth > 0.0f, "Box dimensions must be positive");
	}

	// Creates a box centered on the coordinate origin.
	OrthoBox3D(float width, float height, float depth)
		:OrthoBox3D(glm::vec3(-width / 2.0f, -height / 2.0f, -depth / 2.0f), width, height, depth)
	{
	}

	uint32_t NVertices() override { return 8; }
	uint32_t NIndices() override { return 36; }

	void RenderMesh(MemoryStreamFloat3DAdapter posStream, IndicesMemoryStream& indexStream) override
	{
		posStream << _origin;
		posStream << _origin + glm::vec3(_width, 0.0f, 0.0f);
		posStream << _origin + glm::vec3(_width, _height, 0.0f);
		posStream << _origin + glm::vec3(0.0f, _height, 0.0f);
		posStream << _origin + glm::vec3(0.0f, 0.0f, _depth);
		posStream << _origin + glm::vec3(_width, 0.0f, _depth);
		posStream << _origin + glm::vec3(_width, _height, _depth);
		posStream << _origin + glm::vec3(0.0f, _height, _depth);

		// Counterclockwise winding when each face is viewed from outside the box.
		indexStream << std::array<size_t, 36>{
			0, 2, 1, 0, 3, 2, // -Z
			4, 5, 6, 4, 6, 7, // +Z
			0, 4, 7, 0, 7, 3, // -X
			1, 2, 6, 1, 6, 5, // +X
			0, 1, 5, 0, 5, 4, // -Y
			3, 7, 6, 3, 6, 2  // +Y
		};
	}

	void Draw(IDrawContext& context) override
	{
		context.DrawIndexed();
	}
};
