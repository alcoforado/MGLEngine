#pragma once

#using "NetLibs/GlmNet.dll"
#include <glm/detail/type_vec2.hpp>
ref class BasicTypesMapper
{
public:
	glm::vec2 Map(GlmNet::vec2 o)
	{
		return glm::vec2(o.x, o.y);
	}

};

