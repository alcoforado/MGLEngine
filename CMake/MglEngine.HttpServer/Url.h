#pragma once
#include "Utils.h"
#include <string>
#include <boost/algorithm/string.hpp> 
#include <vector>
#include <map>
class Url
{
	std::vector<std::string> _vpath;
	std::map<std::string, std::string> _query;
public:
	Url(std::string pathQuery)
	{
		std::vector<std::string> vPathQuery;
		boost::split(vPathQuery, pathQuery, boost::is_any_of("?"));


		if (vPathQuery.size() > 1)
		{
			std::string query = vPathQuery[1];
			std::vector<std::string> vQuery;
			boost::split(vQuery, query, boost::is_any_of("&"));
			for (auto q : vQuery)
			{
				std::vector<std::string> t;
				boost::split(t, q, boost::is_any_of("="));
				if (t.size() == 2)
					_query[t[0]] = t[1];
				else if (t.size() == 1)
					_query[t[0]] = "";
			}
			
		}


		std::vector<std::string> v;
		boost::split(v, vPathQuery[0], boost::is_any_of("/"));
		for (auto s : v)
		{
			auto tmp = trim(s);
			if (tmp != "")
				_vpath.push_back(tmp);
		}
		
	}

	const std::vector<std::string>& getPath() { return _vpath; }
	std::map<std::string, std::string>& getQuery() { return _query; }

	std::string relativePath() 
	{
		std::string acum = "";
		for (auto s : _vpath)
		{
			acum += s+"/";
		}
		if (acum.length() > 0)
			return acum.substr(0, acum.length() - 1);
		return "";
	}


};
