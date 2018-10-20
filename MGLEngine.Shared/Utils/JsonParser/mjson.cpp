#include "mjson.h"
#include <MGLEngine.Shared/Utils/JsonParser/json.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "MGLEngine.Shared/Utils/Exception.h"

namespace glm {
	void to_json(json& j, const vec2& v)
	{
		j["x"] = v.x;
		j["y"] = v.y;
	}


	void from_json(const json& j, vec2& v)
	{
		v.x = j["x"];
		v.y = j["y"];
	}

	void to_json(json& j, const vec3& v)
	{
		j["x"] = v.x;
		j["y"] = v.y;
		j["z"] = v.z;
	}
	void from_json(const json& j, vec3& v)
	{
		glm::vec3 r;
		

		if (j.find("r")!=j.end() && j.find("g") != j.end() && j.find("b")!= j.end())
		{
			r.x = j["r"].get<float>();
			r.y = j["g"].get<float>();
			r.z = j["b"].get<float>();
		}
		else if (j.find("x") != j.end() && j.find("y") != j.end() && j.find("z") != j.end())
		{
			r.x = j["x"].get<float>();
			r.y = j["y"].get<float>();
			r.z = j["z"].get<float>();
		}
		else
		{
			throw new Exception("Could not deserialize json to Vec3");
		}
		v=r;



		v.x = j["x"];
		v.y = j["y"];
		v.z = j["z"];
	}

}





json jsonext::SerializeAsColor(std::vector<glm::vec3>& v)
{
	json j = json::array();
	for (glm::vec3 el : v)
	{
		json je = jsonext::SerializeAsColor(el);
		j.push_back(je);

	}
	return j;
}


json jsonext::SerializeAsColor(glm::vec3& v)
{
	json j;
	j["r"] = v.r;
	j["g"] = v.g;
	j["b"] = v.b;
	return j;

}