#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <MGLEngine.Shared/Interfaces/IMesh3D.h>




class MeshUtils {
public:

	struct TopologyWithNormals {
		std::vector<glm::vec3> pos, normals;
		std::vector<unsigned> indices;
		size_t bytesSavedIfIndicesDontExist;

	};


public:
	static TopologyWithNormals ComputeNormals(const std::vector<glm::vec3>& points, std::vector<unsigned>& indicesm, float mergeNormalsAngleThressholdInDegs);
	static TopologyWithNormals ReadTopologyFromMesh(IMesh3DWithNormals& mesh);
		// Compares vertex positions, normals and oriented triangles, ignoring buffer order
		// and bytesSavedIfIndicesDontExist. Inputs must contain valid triangle meshes.
		static bool AreTopologiesEqual(const TopologyWithNormals& first, const TopologyWithNormals& second, float tolerance = 1e-5f);
};
