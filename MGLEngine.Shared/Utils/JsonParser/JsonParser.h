#pragma once
#include "json.hpp"
#include <glm/vec2.hpp>
#include "json_fwd.hpp"
#include "json_fwd.hpp"

class JsonParser : public nlohmann::json
{

public:
	class FieldDescriptor
	{
	public:
		std::string Name;
		std::string Type;
	};

	class TypeDescriptor
	{
	public:
		std::string TypeName;
		std::list<FieldDescriptor> Fields;

	};
	
public:
	JsonParser(const std::string& text);
	JsonParser();
	~JsonParser();

	void AddMember(std::string name, const glm::vec2& v);
	void AddMemberAsColor(std::string name, const std::vector<glm::vec3> &v);
	glm::vec2 GetVec2(std::string memberName);


};

