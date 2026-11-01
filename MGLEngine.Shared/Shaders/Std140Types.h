#pragma once
#include <glm/glm.hpp>
#include <cstddef>
#include <type_traits>

// Marker for types explicitly designed to match a GLSL std140 layout.
// Keep this empty and non-polymorphic: objects are copied directly to GPU memory.
// Deriving from this type does not add padding or validate member offsets.
struct std140 {};

// Column-major GLSL mat2: each column occupies a 16-byte std140 slot.
struct alignas(16) Std140Mat2 : public std140
{
	glm::vec4 Column0;
	glm::vec4 Column1;

	explicit Std140Mat2(const glm::mat2& value = glm::mat2(1.0f))
		: Column0(value[0], 0.0f, 0.0f), Column1(value[1], 0.0f, 0.0f)
	{
	}
};

static_assert(std::is_trivially_copyable_v<Std140Mat2>);
static_assert(std::is_standard_layout_v<Std140Mat2>);
static_assert(alignof(Std140Mat2) == 16);
static_assert(sizeof(Std140Mat2) == 32);
static_assert(offsetof(Std140Mat2, Column0) == 0);
static_assert(offsetof(Std140Mat2, Column1) == 16);
