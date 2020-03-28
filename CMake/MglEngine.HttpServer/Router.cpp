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

void Router::Map_GET(const std::string& relativePath, ControllerCall f)
{
	Url url(relativePath);
	std::string keyPath = getKeyPath(url);


	Router::RouterInfo info{ keyPath,"GET",f,url };
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
						routeParams[*it] = urlPart;

					}
					else if (urlPart != *it)
					{
						isMatch = false;
						break;
					}

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
