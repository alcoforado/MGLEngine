#pragma once
#include <vector>
#include <glm/glm.hpp>




class MeshUtils {
public:

	struct TopologyWithNormals {
		std::vector<glm::vec3> pos, normals;
		std::vector<unsigned> indices;
		size_t bytesSavedIfIndicesDontExist;

	};


public:
	static TopologyWithNormals ComputeNormals(const std::vector<glm::vec3>& points, std::vector<unsigned>& indicesm, float mergeNormalsAngleThressholdInDegs);

};