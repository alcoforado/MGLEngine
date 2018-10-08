#include "JsonParser.h"
#include <glm/vec2.hpp>


JsonParser::JsonParser(const std::string& text)
{
	*(static_cast<nlohmann::json*>(this))=this->parse(text);
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
	(*this)[name].insert()
}

glm::vec2 JsonParser::GetVec2(std::string memberName)
{
	glm::vec2 r;
    auto m = (*this)[memberName];
	r.x=m["x"].get<float>();
	r.y=m["y"].get<float>();
	return r;
}



