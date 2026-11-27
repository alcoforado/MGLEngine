#include <MGLEngine.Shared/Mesh/NormalsAdapter.h>
#include <MGLEngine.Shared/Mesh/OrthoBox3D.h>
#include <MGLEngine.Shared/Mesh/OrthoBox3DN.h>
#include <MGLEngine.Shared/Utils/MeshUtils.h>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

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

    CHECK(MeshUtils::AreTopologiesEqual(actual, expected));
}

TEST_CASE("Topology comparison checks geometry and oriented connectivity", "[MeshUtils][TopologyComparison]")
{
    const MeshUtils::TopologyWithNormals expected{
        .pos = { { 0, 0, 0 }, { 2, 0, 0 }, { 2, 3, 0 }, { 0, 3, 0 } },
        .normals = std::vector<glm::vec3>(4, glm::vec3(0, 0, 1)),
        .indices = { 0, 1, 2, 0, 2, 3 },
        .bytesSavedIfIndicesDontExist = 0
    };
    auto actual = expected;
    bool equal = true;

    SECTION("Identical topology") {}

    SECTION("Vertex order, triangle order and starting corners may differ")
    {
        actual.pos = { expected.pos[2], expected.pos[0], expected.pos[3], expected.pos[1] };
        actual.indices = { 2, 1, 0, 3, 0, 1 };
    }

    SECTION("Storage savings metadata does not affect equality")
    {
        actual.bytesSavedIfIndicesDontExist = 100;
    }

    SECTION("Tolerance applies to positions and normals")
    {
        actual.pos[0].x += 5e-6f;
        actual.normals[0].x += 5e-6f;
        CHECK_FALSE(MeshUtils::AreTopologiesEqual(actual, expected, 1e-6f));
        CHECK(MeshUtils::AreTopologiesEqual(actual, expected, 1e-4f));
    }

    SECTION("Different positions")
    {
        actual.pos[0].x += 0.5f;
        equal = false;
    }

    SECTION("Different normals")
    {
        actual.normals[0].z = -1.0f;
        equal = false;
    }

    SECTION("Reversed triangle winding")
    {
        actual.indices = { 0, 2, 1, 0, 2, 3 };
        equal = false;
    }

    SECTION("Different diagonal connections")
    {
        actual.indices = { 0, 1, 3, 1, 2, 3 };
        equal = false;
    }

    SECTION("A repeated triangle cannot replace another triangle")
    {
        actual.indices = { 0, 1, 2, 0, 1, 2 };
        equal = false;
    }

    SECTION("Different vertex counts")
    {
        actual.pos.push_back({ 1, 1, 0 });
        actual.normals.push_back({ 0, 0, 1 });
        equal = false;
    }

    SECTION("Different triangle counts")
    {
        actual.indices.resize(3);
        equal = false;
    }

    CHECK(MeshUtils::AreTopologiesEqual(actual, expected) == equal);
    CHECK(MeshUtils::AreTopologiesEqual(expected, actual) == equal);
    CHECK(MeshUtils::AreTopologiesEqual(expected, expected, 0.0f));
}

TEST_CASE("Topology comparison resolves coincident vertices by connectivity", "[MeshUtils][TopologyComparison]")
{
    const MeshUtils::TopologyWithNormals expected{
        .pos = { { 0, 0, 0 }, { 0, 0, 0 }, { 2, 0, 0 }, { 2, 3, 0 }, { 0, 3, 0 } },
        .normals = std::vector<glm::vec3>(5, glm::vec3(0, 0, 1)),
        .indices = { 0, 2, 3, 1, 3, 4 },
        .bytesSavedIfIndicesDontExist = 0
    };
    auto actual = expected;
    actual.indices = { 1, 2, 3, 0, 3, 4 };
    CHECK(MeshUtils::AreTopologiesEqual(actual, expected));
    CHECK(MeshUtils::AreTopologiesEqual(expected, actual));

    actual.indices = { 1, 3, 2, 0, 3, 4 };
    CHECK_FALSE(MeshUtils::AreTopologiesEqual(actual, expected));
}

TEST_CASE("Empty topologies compare equal", "[MeshUtils][TopologyComparison]")
{
    CHECK(MeshUtils::AreTopologiesEqual({}, {}));
}
