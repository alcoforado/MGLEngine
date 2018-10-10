#include "JsonParser.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "MGLEngine.Shared/Utils/Exception.h"


JsonParser::JsonParser(const std::string& text)
{
	
	*(static_cast<nlohmann::json*>(this)) = this->parse(text);
}

JsonParser::JsonParser(const nlohmann::json& j)
{
	*(static_cast<nlohmann::json*>(this)) = j;
}

JsonParser::JsonParser()
{
}


JsonParser::~JsonParser()
{
}

JsonParser& JsonParser::operator[](const char *str)
{
	assert(sizeof(JsonParser) == sizeof(nlohmann::json));
	nlohmann::json &j = static_cast<nlohmann::json&>(*this)[str];
	return static_cast<JsonParser&>(j);
}

JsonParser & JsonParser::operator[](const std::string & str)
{
	return this->operator[](str.c_str());
}

JsonParser& JsonParser::operator=(glm::vec2& v)
{
	this->clear();
	(*this)["x"] = v.x;
	(*this)["y"] = v.y;
	
	return *this;
}

JsonParser& JsonParser::operator=(glm::vec3& v)
{
	this->clear();
	
	(*this)["x"] = v.x;
	(*this)["y"] = v.y;
	(*this)["z"] = v.z;

	return *this;
}



JsonParser& JsonParser::operator=(float x)
{
	static_cast<nlohmann::json&>(*this) = x;
	return *this;
}

bool JsonParser::exist(const std::string& key) const 
{
	return this->find(key) != this->end();
}


JsonParser JsonParser::SerializeAsColor(glm::vec3& v)
{
	JsonParser j;
	j["r"] = v.r;
	j["g"] = v.g;
	j["b"] = v.b;
	return j;

}

JsonParser::operator glm::vec2() const
{
	glm::vec2 r;
	const nlohmann::json& m = (*this);
	r.x = m["x"].get<float>();
	r.y = m["y"].get<float>();
	return r;

}


JsonParser::operator glm::vec3() const
{
	glm::vec3 r;
	const nlohmann::json &j = static_cast<const nlohmann::json&>(*this);

	if (exist("r") && exist("g") && exist("b"))
	{
		r.x = j["r"].get<float>();
		r.y = j["g"].get<float>();
		r.z = j["b"].get<float>();
	}
	else if (!j["x"].is_null() && !j["y"].is_null() && !j["z"].is_null())
	{
		r.x = j["x"].get<float>();
		r.y = j["y"].get<float>();
		r.z = j["z"].get<float>();
	}
	else
	{
		throw new Exception("Could not deserialize json to Vec3");
	}
	return r;
}




