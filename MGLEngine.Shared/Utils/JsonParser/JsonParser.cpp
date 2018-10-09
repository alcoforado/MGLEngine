#include "JsonParser.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <MGLEngine.Shared/Utils/Exception.h>

JsonParser::JsonParser(const std::string& text)
{
	_json=_json.parse(text);
}




JsonParser::JsonParser(const nlohmann::json & j)
	:_json(j)
{
	
}

JsonParser::JsonParser()
{
	
}


JsonParser::~JsonParser()
{
}

void JsonParser::AddMember(std::string name, const glm::vec2& v)
{
	(*this)[name] = { {"x",v.x},{"y",v.y} };
}

void JsonParser::AddMemberAsColor(std::string name, const std::vector<glm::vec3>& v)
{
	(*this)[name] = this->array();
	for (auto color : v)
	{
		(*this)[name].push_back(JsonParser::SerializeColor(color));
	}
}

glm::vec2 JsonParser::GetVec2(std::string memberName)
{
	glm::vec2 r;
    auto m = (*this)[memberName];
	r.x=m["x"].get<float>();
	r.y=m["y"].get<float>();
	return r;
}

JsonParser JsonParser::SerializeColor(glm::vec3 c)
{
	JsonParser j;
	j["r"] = c.r;
	j["g"] = c.g;
	j["b"] = c.b;
	return j;
}

JsonParser& JsonParser::operator[](std::string str)
{
	return JsonParser(_json[str]);
}



glm::vec3 JsonParser::ToVec3(nlohmann::json & j)
{
	glm::vec3 v;
	if (j.find("r")!=j.end())
	{
		v.r = j["r"];
		v.b = j["b"];
		v.g = j["g"];
	}
	else if (j.find("x") != j.end())
	{
		v.x = j["x"];
		v.y = j["y"];
		v.z = j["z"];
	}
	else
	{
		throw new Exception("Json is not a vec3");
	}
	return v;
}

JsonParser::operator glm::vec3&()
{
	{ return ToVec3(_json); }
}




