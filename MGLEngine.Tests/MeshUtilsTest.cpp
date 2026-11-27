#include <MGLEngine.Shared/Mesh/NormalsAdapter.h>
#include <MGLEngine.Shared/Mesh/OrthoBox3D.h>
#include <MGLEngine.Shared/Mesh/OrthoBox3DN.h>
#include <MGLEngine.Shared/Utils/MeshUtils.h>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <array>

namespace {
    

    std::vector<std::array<unsigned, 3>> CanonicalTriangles(const std::vector<unsigned>& indices)
    {
        REQUIRE(indices.size() % 3 == 0);
        std::vector<std::array<unsigned, 3>> triangles;
        for (size_t i = 0; i < indices.size(); i += 3)
        {
            const auto a = indices[i];
            const auto b = indices[i + 1];
            const auto c = indices[i + 2];
            // Cyclic rotations preserve winding; reversing the corners does not.
            triangles.push_back(std::min({
                std::array<unsigned, 3>{ a, b, c },
                std::array<unsigned, 3>{ b, c, a },
                std::array<unsigned, 3>{ c, a, b }
            }));
        }
        std::sort(triangles.begin(), triangles.end());
        return triangles;
    }
}

TEST_CASE("ComputeNormals returns unit length normals", "[MeshUtils]")
{
    const std::vector<glm::vec3> points{
        { 0.0f, 0.0f, 0.0f },
        { 2.0f, 0.0f, 1.0f },
        { 0.0f, 3.0f, 1.0f },
        { 2.0f, 3.0f, 3.0f }
    };
    std::vector<unsigned> indices;
    float mergeAngle = 45.0f;

    SECTION("A single triangle")
    {
        indices = { 0, 1, 2 };
    }

    SECTION("Adjacent triangles with merged normals")
    {
        indices = { 0, 1, 2, 1, 3, 2 };
    }

    SECTION("Adjacent triangles with separate normals")
    {
        indices = { 0, 1, 2, 1, 3, 2 };
        mergeAngle = 5.0f;
    }

    const auto topology = MeshUtils::ComputeNormals(points, indices, mergeAngle);

    REQUIRE_FALSE(topology.normals.empty());
    REQUIRE(topology.normals.size() == topology.pos.size());
    for (size_t i = 0; i < topology.normals.size(); i++)
    {
        CAPTURE(i);
        CHECK(glm::length(topology.normals[i]) == Catch::Approx(1.0f).margin(1e-5f));
    }
}

TEST_CASE("OrthoBox3DN and NormalsAdapter produce the same topology", "[MeshUtils][OrthoBox3D]")
{
    // Unequal dimensions and a translated origin make axis mixups visible.
    const glm::vec3 origin(0, 0, 0);
    OrthoBox3DN boxWithNormals(origin, 2.0f, 3.0f, 5.0f);
    OrthoBox3D box(origin, 2.0f, 3.0f, 5.0f);
    NormalsAdapter adaptedBox(box);

    REQUIRE(boxWithNormals.NVertices() == 24);
    REQUIRE(boxWithNormals.NIndices() == 36);
    REQUIRE(adaptedBox.NVertices() == boxWithNormals.NVertices());
    REQUIRE(adaptedBox.NIndices() == boxWithNormals.NIndices());

    const auto expected = MeshUtils::ReadTopologyFromMesh(boxWithNormals);
    const auto actual = MeshUtils::ReadTopologyFromMesh(adaptedBox);

    // Match each vertex once by position and normal, allowing different numbering.
    std::vector<unsigned> vertexMap(actual.pos.size());
    std::vector<bool> matched(expected.pos.size(), false);
    for (size_t i = 0; i < actual.pos.size(); i++)
    {
        CAPTURE(i);
        bool found = false;
        for (size_t j = 0; j < expected.pos.size(); j++)
        {
            if (!matched[j]
                && glm::length(actual.pos[i] - expected.pos[j]) < 1e-5f
                && glm::length(actual.normals[i] - expected.normals[j]) < 1e-5f)
            {
                vertexMap[i] = static_cast<unsigned>(j);
                matched[j] = true;
                found = true;
                break;
            }
        }
        REQUIRE(found);
    }

    std::vector<unsigned> mappedIndices;
    for (const auto index : actual.indices)
    {
        REQUIRE(index < vertexMap.size());
        mappedIndices.push_back(vertexMap[index]);
    }
    for (const auto index : expected.indices)
    {
        REQUIRE(index < expected.pos.size());
    }
    CHECK(CanonicalTriangles(mappedIndices) == CanonicalTriangles(expected.indices));
}
