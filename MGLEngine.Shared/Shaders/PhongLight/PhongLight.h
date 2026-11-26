#pragma once

#include <MGLEngine.Shared/common.h>
#include <MGLEngine.Shared/MGLEngine.h>
#include <glm/glm.hpp>
class PhongLight : public IDrawingObject {
private:
	IMesh3DWithNormals& _mesh;
	std::vector<glm::vec3> _colors;
public:
	PhongLight(MGLEngine& engine, IMesh3DWithNormals& mesh,const std::vector<glm::vec3>& colors);

	 uint32_t NVertices() override {
		return _mesh.NVertices();
	}
	 uint32_t NIndices() override {
		return _mesh.NIndices();
	}

	 void RenderData(RenderSerializationContext& context) override;
};

