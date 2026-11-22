#pragma once
#include <glm/glm.hpp>
class Light {
	glm::vec3 pos;
	glm::vec3 direction;
	glm::vec3 color;
	float ambientStrength;
	




public:
	Light(glm::vec3& ppos, glm::vec3& pdirection, glm::vec3& pcolor)
		:pos(ppos), direction(pdirection), color()
	{
	}


};