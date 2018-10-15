#pragma once
#include "json.hpp"
#include <glm/vec2.hpp>
#include "json_fwd.hpp"
#include "json_fwd.hpp"
#include "MGLEngine.Shared/Utils/Exception.h"

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
	JsonParser(const nlohmann::json& j);
	JsonParser();
	~JsonParser();

	//nlohmann::json& to_base_json()
	//{
	
	//}

	JsonParser& operator[](const char* str);
	JsonParser& operator[](const std::string& str);


	JsonParser& operator=(glm::vec2& v);
	JsonParser& operator=(glm::vec3 & v);
	JsonParser& operator=(float x);

	bool exist(const std::string& key) const;
	static JsonParser SerializeAsColor(std::vector<glm::vec3>&v );
	static JsonParser SerializeAsColor(glm::vec3 & v);
	
	operator glm::vec2() const;
	operator glm::vec3() const;


	template<class T>
	JsonParser& operator=(const std::vector<T> &v)
	{
		*this = nlohmann::json::array();
		for(auto t : v)
		{
			JsonParser elem;
			elem = t;
			this->push_back(elem);
		}
		return *this;

	}



	template<class T>
	operator std::vector<T>() const
	{
		std::vector<T> result;
		if (!this->is_array())
		{
			throw new Exception("Json is not an array");
		}
		for (auto it : this->items())
		{
			nlohmann::json j = *it;
			T t = JsonParser(j);
			result.push_back(t);

		}
		return result;


	}






};

