#pragma once
#include "HttpContext.h"
#include <map>
class WebApiContext {
private:
	HttpContext& _context;
	std::map<std::string, std::string> &_routeParams;

public:
	WebApiContext(HttpContext& pContext,std::map<std::string,std::string> &routeParams) :_context(pContext),_routeParams(routeParams) {}

	const std::map<std::string, std::string>& getRouteParameters() { return _routeParams; }

};

