#pragma once

#using "NetLibs/GlmNet.dll"
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <vector>
using namespace System::Collections::Generic;
ref class BasicTypesMapper
{
public:
	glm::vec2 Map(GlmNet::vec2 o)
	{
		return glm::vec2(o.x, o.y);
	}

	glm::vec3 Map(GlmNet::vec3 o)
	{
		return glm::vec3(o.x, o.y, o.z);
	}
	
	
	template<class T,class O>
	std::vector<O> MapList(List<T>^list)
	{
		std::vector<O> result(list->Count);
		int i = 0;
		for each (auto elem in list)
		{
			result[i++] = Map(elem);
		}
		return result;
	}
	/*
	std::vector<glm::vec3>* Map2(List<GlmNet::vec3>^ lst)
	{
		return this->MapList<GlmNet::vec3,glm::vec3>(lst);
	}
	*/


};

