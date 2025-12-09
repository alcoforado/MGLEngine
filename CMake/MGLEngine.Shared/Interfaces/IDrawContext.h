#pragma once
#include <cstdint>
class IDrawContext
{
	public:
		virtual void DrawIndexedTriangles() = 0;
};