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
#include "HttpResponse.h"




class Router
{
public:
	using ControllerCall = std::function<HttpResponse(WebApiContext&)>;

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
	void Map(http::verb method,const std::string& relativePath, ControllerCall f);
	std::shared_ptr<RouteMatch> MatchRoute(const Url& url,std::string method);

	static std::string HttpMethodToString(http::verb method);
	static http::verb parseHttpMethod(std::string method);

	
	

};
