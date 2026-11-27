#pragma once

#include "MeshUtils.h"
#include <algorithm>
#include <array>
#include <cmath>
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

namespace {

	using Triangle = std::array<unsigned, 3>;

	Triangle CanonicalTriangle(unsigned a, unsigned b, unsigned c)
	{
		// Cyclic rotations preserve winding; reversing the corners does not.
		return std::min({ Triangle{ a, b, c }, Triangle{ b, c, a }, Triangle{ c, a, b } });
	}

	void AssertValidTopology(const MeshUtils::TopologyWithNormals& topology)
	{
		eassert(topology.pos.size() == topology.normals.size(), "Each vertex must have a normal");
		eassert(topology.indices.size() % 3 == 0, "Indices must describe complete triangles");
		for (const auto index : topology.indices)
		{
			eassert(index < topology.pos.size(), "Vertex index is out of range");
		}
	}
}

bool MeshUtils::AreTopologiesEqual(const TopologyWithNormals& first, const TopologyWithNormals& second, float tolerance)
{
	eassert(std::isfinite(tolerance) && tolerance >= 0.0f, "Tolerance must be finite and nonnegative");
	AssertValidTopology(first);
	AssertValidTopology(second);
	if (first.pos.size() != second.pos.size() || first.indices.size() != second.indices.size())
	{
		return false;
	}

	std::vector<Triangle> expectedTriangles;
	for (size_t i = 0; i < second.indices.size(); i += 3)
	{
		expectedTriangles.push_back(CanonicalTriangle(second.indices[i], second.indices[i + 1], second.indices[i + 2]));
	}
	std::sort(expectedTriangles.begin(), expectedTriangles.end());

	// Equal vertices must also occur in the same number of triangle corners.
	std::vector<size_t> firstUses(first.pos.size(), 0), secondUses(second.pos.size(), 0);
	for (const auto index : first.indices) { firstUses[index]++; }
	for (const auto index : second.indices) { secondUses[index]++; }

	const size_t unmapped = std::numeric_limits<size_t>::max();
	std::vector<size_t> vertexMap(first.pos.size(), unmapped);
	std::vector<bool> used(second.pos.size(), false);
	std::vector<std::vector<size_t>> candidates(first.pos.size());
	for (size_t i = 0; i < first.pos.size(); i++)
	{
		for (size_t j = 0; j < second.pos.size(); j++)
		{
			if (firstUses[i] == secondUses[j]
				&& glm::length(first.pos[i] - second.pos[j]) <= tolerance
				&& glm::length(first.normals[i] - second.normals[j]) <= tolerance)
			{
				candidates[i].push_back(j);
			}
		}
		if (candidates[i].empty()) { return false; }
		if (candidates[i].size() == 1)
		{
			const auto match = candidates[i].front();
			if (used[match]) { return false; }
			vertexMap[i] = match;
			used[match] = true;
		}
	}

	auto trianglesMatch = [&]() {
		std::vector<Triangle> mappedTriangles;
		for (size_t i = 0; i < first.indices.size(); i += 3)
		{
			const auto a = vertexMap[first.indices[i]];
			const auto b = vertexMap[first.indices[i + 1]];
			const auto c = vertexMap[first.indices[i + 2]];
			if (a != unmapped && b != unmapped && c != unmapped)
			{
				mappedTriangles.push_back(CanonicalTriangle(static_cast<unsigned>(a), static_cast<unsigned>(b), static_cast<unsigned>(c)));
			}
		}
		std::sort(mappedTriangles.begin(), mappedTriangles.end());
		// Includes also checks triangle multiplicity, including duplicate triangles.
		return std::includes(expectedTriangles.begin(), expectedTriangles.end(), mappedTriangles.begin(), mappedTriangles.end());
	};

	// Coincident vertices can have identical normals but different connections.
	// Try alternative bijections only where the vertex attributes are ambiguous.
	auto matchRemaining = [&](auto&& self) -> bool {
		size_t next = unmapped;
		size_t fewestMatches = std::numeric_limits<size_t>::max();
		for (size_t i = 0; i < vertexMap.size(); i++)
		{
			if (vertexMap[i] != unmapped) { continue; }
			size_t available = 0;
			for (const auto candidate : candidates[i]) { if (!used[candidate]) { available++; } }
			if (available == 0) { return false; }
			if (available < fewestMatches)
			{
				next = i;
				fewestMatches = available;
			}
		}
		if (next == unmapped) { return true; }
		for (const auto candidate : candidates[next])
		{
			if (used[candidate]) { continue; }
			vertexMap[next] = candidate;
			used[candidate] = true;
			if (trianglesMatch() && self(self)) { return true; }
			used[candidate] = false;
			vertexMap[next] = unmapped;
		}
		return false;
	};

	return trianglesMatch() && matchRemaining(matchRemaining);
}
