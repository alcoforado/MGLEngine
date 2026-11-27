#pragma once
#include <MGLEngine.Shared/Interfaces/IMesh3D.h>
#include <array>
#include <glm/vec3.hpp>

class OrthoBox3DN : public IMesh3DWithNormals {
private:
	glm::vec3 _origin;
	float _width;
	float _height;
	float _depth;

public:


	// The origin is the minimum corner; dimensions extend along +X, +Y and +Z.
	OrthoBox3DN(glm::vec3 origin, float width, float height, float depth)
		:_origin(origin), _width(width), _height(height), _depth(depth)
	{
		eassert(width > 0.0f && height > 0.0f && depth > 0.0f, "Box dimensions must be positive");
	}

	// Creates a box centered on the coordinate origin.
	OrthoBox3DN(float width, float height, float depth)
		:OrthoBox3DN(glm::vec3(-width / 2.0f, -height / 2.0f, -depth / 2.0f), width, height, depth)
	{
	}

	uint32_t NVertices() override { return 24; }
	uint32_t NIndices() override { return 36; }

	void RenderMesh(MemoryStreamFloat3DAdapter posStream, IndicesMemoryStream& indexStream, MemoryStreamFloat3DAdapter normals) override
	{
		glm::vec3 X00 = _origin;
		glm::vec3 X10 = _origin + glm::vec3(_width, 0.0f, 0.0f);
		glm::vec3 X11 = _origin + glm::vec3(_width, _height, 0.0f);
		glm::vec3 X01 = _origin + glm::vec3(0.0f, _height, 0.0f);
		glm::vec3 Z00 = _origin + glm::vec3(0.0f, 0.0f, _depth);
		glm::vec3 Z10 = _origin + glm::vec3(_width, 0.0f, _depth);
		glm::vec3 Z11 = _origin + glm::vec3(_width, _height, _depth);
		glm::vec3 Z01 = _origin + glm::vec3(0.0f, _height, _depth);

		// Counterclockwise winding when each face is viewed from outside the box.
		//Z-
		glm::vec3 normal(0, 0, -1);
		posStream << std::array<glm::vec3,4>{X00, X10, X11, X01};
		indexStream << std::array<size_t, 6>{0, 2, 1, 0, 3, 2}; //Z-
		normals << normal << normal << normal << normal;
		
		//Z+
		normal = glm::vec3(0, 0, 1);
		posStream << std::array<glm::vec3,4>{Z00, Z10, Z11, Z01};
		indexStream << std::array<size_t, 6>{4, 6, 5, 4, 7, 6};
		normals << normal << normal << normal << normal;
		                                                         
		//X-
		normal = glm::vec3(-1, 0, 0);
		posStream << std::array<glm::vec3,4>{X00, Z00, Z01, X01};
		indexStream << std::array<size_t, 6>{8, 9, 10, 10, 11, 8};
		normals << normal << normal << normal << normal;

		//X+
		normal = glm::vec3(1, 0, 0);
		posStream << std::array<glm::vec3,4>{X10, X11, Z11, Z10};
		indexStream << std::array<size_t, 6>{12, 13, 14, 14, 15, 12};
		normals << normal << normal << normal << normal;

		//Y-
		normal = glm::vec3(0, -1, 0);
		posStream << std::array<glm::vec3,4>{X00, X10, Z10, Z00};
		indexStream << std::array<size_t, 6>{16, 17, 18, 18, 19, 16};
		normals << normal << normal << normal << normal;

		//Y+
		normal = glm::vec3(0, 1, 0);
		posStream << std::array<glm::vec3,4>{X01, Z01, Z11, X11};
		indexStream << std::array<size_t, 6>{20, 21, 22, 22, 23, 20};
		normals << normal << normal << normal << normal;

				
		
	}

	void Draw(IDrawContext& context) override
	{
		context.DrawIndexed();
	}
};
