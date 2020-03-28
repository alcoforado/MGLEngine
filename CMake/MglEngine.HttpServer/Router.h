#pragma once

#include <string>
#include "Utils.h"
#include <map>
#include <vector>
#include <list>
#include <functional>
#include "boost_deps.h"
#include "WebApiContext.h"
#include "Url.h"



class Router
{
public:
	using ControllerCall = std::function<http::response<http::string_body>(WebApiContext&)>;

private:
	struct RouterInfo {
		std::string keyPath;
		std::string httpMethod;
		ControllerCall f;
		Url path;

	};

	struct RouteMatch {
		std::map<std::string, std::string>  RouteParameters;
		ControllerCall handlerFunction;
		
	};

	using RouteTable = std::list<Router::RouterInfo>;
	RouteTable Table;
public:
	Router() {}
	void Map_GET(const std::string& relativePath, ControllerCall f);
	std::shared_ptr<RouteMatch> MatchRoute(Url& url,std::string method);

	
	
	

};
