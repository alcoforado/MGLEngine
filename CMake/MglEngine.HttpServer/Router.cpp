#include "Router.h"

#include "Utils.h"

std::string getKeyPath(Url& url)
{
	std::string keyPath;
	for (auto terms : url.getPath())
	{
		if (delimitedBy(terms, "{", "}"))
		{
			break;
		}
		keyPath += terms + "/";
	}
	return trim(keyPath, "/");
}

void Router::Map(http::verb method,const std::string& relativePath, ControllerCall f)
{
	Url url(relativePath);
	std::string keyPath = getKeyPath(url);


	Router::RouterInfo info{ keyPath,HttpMethodToString(method),f,url };
	Table.push_back(info);



}

std::shared_ptr<Router::RouteMatch> Router::MatchRoute(Url& url,std::string method)
{
	std::map<std::string, std::string> routeParams;
	auto strPath = url.relativePath();
	for (auto route : Table)
	{
		if (method == route.httpMethod && hasPrefix(route.keyPath,strPath))
		{
			if (url.getPath().size() == route.path.getPath().size())
			{
				auto it = route.path.getPath().cbegin();
				bool isMatch = true;
				for (auto urlPart : url.getPath())
				{
					if (delimitedBy(*it, "{", "}"))
					{
						std::string pName=trim(*it, "{}");
						routeParams[pName] = urlPart;

					}
					else if (urlPart != *it)
					{
						isMatch = false;
						break;
					}
					it++;
				}
				if (isMatch) {
					auto p = std::shared_ptr<Router::RouteMatch>(new Router::RouteMatch());
					p->handlerFunction = route.f;
					p->RouteParameters = std::move(routeParams);
					return p;
				}

			}


		}
	}
	return NULL;

}

std::string Router::HttpMethodToString(http::verb method)
{
	switch (method)
	{
	case http::verb::get:
		return "GET";
	case http::verb::post:
		return "POST";
	case http::verb::put:
		return "PUT";
	case http::verb::delete_:
		return "DELETE";
	default:
		return "SomethingElse";
	}
	return std::string();
}

http::verb Router::parseHttpMethod(std::string method)
	{
		if (method == "GET")
			return http::verb::get;
		else if (method == "POST")
			return http::verb::post;
		else if (method == "PUT")
			return http::verb::put;
		else if (method == "DELETE")
			return http::verb::delete_;
		else if (method == "PUT")
			return http::verb::post;
		else
			throw std::exception("invalid method");

	}
	