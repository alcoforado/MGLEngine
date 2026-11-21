#pragma once

#include <MGLEngine.Shared/common.h>
#include <MGLEngine.Shared/MGLEngine.h>
#include <glm/glm.hpp>
class PhongLight : public IDrawingObject {
private:
	IMesh3D& _mesh;

public:
	PhongLight(MGLEngine& engine, IMesh3DWithNormals& mesh);

	virtual uint32_t NVertices() override {
		return _mesh.NVertices();
	}
	virtual uint32_t NIndices() override {
		return _mesh.NIndices();
	}
};

