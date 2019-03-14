#pragma once
#include <map>
#include <sstream>
#pragma once



#include <MGLEngine.Shared/Utils/collection_functions.h>

class UniqueNameGenerator
{
	std::map<std::string, int> _nameCount;
public:
	std::string GenerateName(std::string name)
	{
		if (!mstd::Does(_nameCount).Have(name))
		{
			_nameCount[name] = 0;
		}
		std::stringstream ss;
		ss << name << "_" << _nameCount[name]++;
		return ss.str();
	}
};

