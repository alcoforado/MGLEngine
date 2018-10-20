#pragma once
#include "json.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>




typedef nlohmann::json json;
namespace  jsonext
{
	json SerializeAsColor(glm::vec3& v);
	json SerializeAsColor(std::vector<glm::vec3>& v);
};


namespace glm
{
	void to_json(json& j, const glm::vec2& v);
	void from_json(const json& j, glm::vec2& v);
	void to_json(json& j, const glm::vec3& v);
	void from_json(const json& j, glm::vec3& v);




}




