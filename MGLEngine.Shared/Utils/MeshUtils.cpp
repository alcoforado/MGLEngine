#pragma once

#include "MeshUtils.h"
#include <unordered_map>
#include <string>
#include "eassert.h"
#include <limits>
#include <deque>
#include "math.h"


struct TriangleData {
	size_t index;
	size_t newVertIndex;
	size_t invalid_index = std::numeric_limits<size_t>::max();

	TriangleData(size_t paramIndex)
	{
		index = paramIndex;
		newVertIndex = invalid_index;
	}

	bool NewVerticeAllocated() { return newVertIndex != invalid_index; }
};

struct VertexData {
	std::vector<TriangleData> triangles;

	void SetNewVertForTriangle(size_t triangleIndex, size_t newVertIndex)
	{
		for (auto& elem : triangles)
		{
			if (elem.index == triangleIndex)
			{
				elem.newVertIndex = newVertIndex;
				return;
			}
		}
		eassert(false, "Triangle Index not found");
	}
	
};

MeshUtils::TopologyWithNormals MeshUtils::ComputeNormals(const std::vector<glm::vec3>& points, std::vector<unsigned>& indices, float mergeNormalsAngleThressholdInDegs)
{
	//Build Edges
	eassert(indices.size() % 3 == 0, "Data mismatch");
	size_t triangleI = 0;
	std::vector<VertexData> vertMap(points.size());
	std::vector<glm::vec3> normals;
	normals.reserve(indices.size() / 3);
	for (size_t i = 0; i < indices.size(); i += 3, triangleI++)
	{
		unsigned v0 = indices[i];
		unsigned v1 = indices[i + 1];
		unsigned v2 = indices[i + 2];

		glm::vec3 normal = glm::cross(points[v1] - points[v0], points[v2] - points[v0]);
		normals.push_back(glm::normalize(normal));

		vertMap[v0].triangles.push_back(TriangleData(triangleI));
		vertMap[v1].triangles.push_back(TriangleData(triangleI));
		vertMap[v2].triangles.push_back(TriangleData(triangleI));


	}

	//calculate threeshold
	float limit = fabs(cos(degToRad(mergeNormalsAngleThressholdInDegs)));



	std::deque<glm::vec3> outPos;
	std::deque<glm::vec3> outNormals;
	std::deque<unsigned> nNormalsAdded;
	std::vector<unsigned> outIndices;
	outIndices.reserve(indices.size());

	//Iterate over triangles again
	triangleI = 0;
	for (size_t i = 0; i < indices.size(); i += 3, triangleI++)
	{
		unsigned v0 = indices[i];
		unsigned v1 = indices[i + 1];
		unsigned v2 = indices[i + 2];

		unsigned vertices[3] = { v0,v1,v2 };

		for (unsigned v : vertices)
		{
			bool foundVerticeToReuse = false;
			for (auto& triangle : vertMap[v].triangles)
			{
				if (triangle.index != triangleI && triangle.NewVerticeAllocated())
				{
					auto cosAlpha = glm::dot(normals[triangleI], normals[triangle.index]);
					if (cosAlpha > limit)
					{
						//Reuse the vertex of the triangle
						vertMap[v].SetNewVertForTriangle(triangleI, triangle.newVertIndex);
						outIndices.push_back(static_cast<unsigned>(triangle.newVertIndex));
						outNormals[triangle.newVertIndex] += normals[triangleI];
						nNormalsAdded[triangle.newVertIndex]++;
						foundVerticeToReuse = true;
					}

				}
			}
			if (!foundVerticeToReuse)
			{
				size_t newVerticeIndex = outPos.size();
				vertMap[v].SetNewVertForTriangle(triangleI, newVerticeIndex);
				outPos.push_back(points[v]);
				outIndices.push_back(static_cast<unsigned>(newVerticeIndex));
				outNormals.push_back(normals[triangleI]);
				nNormalsAdded.push_back(1);
			}
		}
	}
	//Last but not least, normalize the normals, when they have more than one contribution
	//Vertices Merged
	size_t verticesMerged = 0;
	for (size_t i = 0; i < outNormals.size(); i++)
	{
		if (nNormalsAdded[i] != 1)
		{
			outNormals[i] = glm::normalize(outNormals[i]);
			verticesMerged += nNormalsAdded[i] - 1;
		}

	}
	

	return TopologyWithNormals{
		.pos = std::vector<glm::vec3>(outPos.begin(),outPos.end()),
		.normals = std::vector<glm::vec3>(outNormals.begin(),outNormals.end()),
		.indices = std::vector<unsigned>(outIndices),
		.bytesSavedIfIndicesDontExist = (outIndices.size() - verticesMerged * 6) * 4
	};

};


MeshUtils::TopologyWithNormals MeshUtils::ReadTopologyFromMesh(IMesh3DWithNormals& mesh)
{
	MeshUtils::TopologyWithNormals topology{};
	topology.pos.resize(mesh.NVertices());
	topology.normals.resize(mesh.NVertices());
	topology.indices.resize(mesh.NIndices());

	InterleavedMemoryStream positions(topology.pos);
	InterleavedMemoryStream normals(topology.normals);
	IndicesMemoryStream indices(topology.indices.data(), topology.indices.size(), 0);
	mesh.RenderMesh(MemoryStreamFloat3DAdapter(positions), indices, MemoryStreamFloat3DAdapter(normals));
	return topology;
}
